/*

This example reads from the default PCM device
and writes to standard output for 5 seconds of data.

*/

/* Use the newer ALSA API */
#define ALSA_PCM_NEW_HW_PARAMS_API

#include <sys/stat.h>
#include <alsa/asoundlib.h>

/**************************************************************/
#define ID_RIFF 0x46464952
#define ID_WAVE 0x45564157
#define ID_FMT 0x20746d66
#define ID_DATA 0x61746164

typedef unsigned long uint32_t;
typedef unsigned short uint16_t;

#define FORMAT_PCM 1

#define RATE 8000
#define CHANNEL 1
//#define INTERLEAVED  


static uint32_t totle_size = 0;

struct wav_header {
    /* RIFF WAVE Chunk */
    uint32_t riff_id;
    uint32_t riff_sz;
    uint32_t riff_fmt;
    /* Format Chunk */
    uint32_t fmt_id;
    uint32_t fmt_sz;
    uint16_t audio_format;
    uint16_t num_channels;
    uint32_t sample_rate;
    uint32_t byte_rate; /* sample_rate * num_channels * bps / 8 */
    uint16_t block_align; /* num_channels * bps / 8 */
    uint16_t bits_per_sample;
    /* Data Chunk */
    uint32_t data_id;
    uint32_t data_sz;
}__attribute__((packed));

static struct wav_header hdr;

			uint32_t  GetSFileize (const char *f)
			{
				struct stat sb;
				if ( stat(f, &sb) == -1 )
				{
					return 0;
				}
				return sb.st_size;
			}

/**************************************************************/
int playback_file(unsigned rate, uint16_t channels, int fd, uint32_t total_count)
{
    int rc;
    int size;
    uint32_t left_size;
    snd_pcm_t *handle;
    snd_pcm_hw_params_t *params;
	#ifdef INTEL
    int dir;
	#endif
    snd_pcm_uframes_t frames;
    char *buffer;                    /* TODO */

	/* Allocate a hardware parameters object. */
	rc = snd_pcm_hw_params_malloc(&params);
				if (rc < 0)
				{
					fprintf(stderr, "snd_pcm_hw_params_malloc: %s\n", snd_strerror(rc));
					exit(1);
   				}
	
    /* Open PCM device for playbacking. */
    rc = snd_pcm_open(&handle, "default", SND_PCM_STREAM_PLAYBACK, 0);
	//rc = snd_pcm_open(&handle, "default", SND_PCM_STREAM_CAPTURE, 0);
    if (rc < 0) {
        fprintf(stderr, "unable to open pcm device: %s\n", snd_strerror(rc));
        exit(1);
    }
   
   
    /* Fill it in with default values. */
    rc = snd_pcm_hw_params_any(handle, params);
				if (rc < 0)
				{
					fprintf(stderr, "snd_pcm_hw_params_any: %s\n", snd_strerror(rc));
					return 1;
				}
				
    /* Set the desired hardware parameters. */
    /* Interleaved mode */
	#ifdef INTERLEAVED
    rc = snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
	#else
	rc = snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_NONINTERLEAVED);
	#endif
				if (rc < 0) 
				{
					fprintf(stderr, "snd_pcm_hw_params_set_access: %d %s\n", rc, snd_strerror(rc));
					//return 1;
				}	
	

    /* Signed 16-bit little-endian format */
    snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE);

    /* Two channels (stereo) */
    snd_pcm_hw_params_set_channels(handle, params, channels);

    /* 44100 bits/second sampling rate (CD quality) */
	#ifdef INTEL
    snd_pcm_hw_params_set_rate_near(handle, params, &rate, &dir);
	#else
	snd_pcm_hw_params_set_rate_near(handle, params, &rate, 0);
	#endif
	

    /* Set period size to 32 frames. */
    frames = 32;
	#ifdef INTEL
    snd_pcm_hw_params_set_period_size_near(handle, params, &frames, &dir);
	#else
	snd_pcm_hw_params_set_period_size_near(handle, params, &frames, 0);
	#endif

    /* Write the parameters to the driver */
    rc = snd_pcm_hw_params(handle, params);
    if (rc < 0) {
        fprintf(stderr, "unable to set hw parameters: %s\n", snd_strerror(rc));
        exit(1);
    }

    /* Use a buffer large enough to hold one period */
	#ifdef INTEL
    snd_pcm_hw_params_get_period_size(params, &frames, &dir);
	#else
	snd_pcm_hw_params_get_period_size(params, &frames, 0);
	#endif
	fprintf(stderr, "get period size: %d\n", frames);
    
    size = frames * 16 / 8 * channels; /* 2 bytes/sample(16bit), 2 channels */
	
    buffer = (char *) malloc(size);
    
 //   while (left_size > 0) {
    while (1) {
        rc = read(fd, buffer, size);
		if(rc <= 0) {
			printf("at the end of file, exiting...\n");
			break;
			}
			
        totle_size += rc;                        /* totle data size */
        left_size = total_count - totle_size;
        if (rc != size)
         fprintf(stderr, "short read: read %d bytes\n", rc);
    
		#ifdef INTERLEAVED
        rc = snd_pcm_writei(handle, buffer, frames);
		#else
		void* Data[2];
		Data[0] = (void*)buffer;
		Data[1] = (void*)buffer;
		rc = snd_pcm_writen(handle, Data, frames);
		#endif
		
        if (rc == -EPIPE) {
         /* EPIPE means overrun */
         fprintf(stderr, "overrun occurred\n");
         snd_pcm_prepare(handle);
        } else if (rc < 0) {
         fprintf(stderr, "error from write: %s\n", snd_strerror(rc));
        } else if (rc != (int)frames) {
         fprintf(stderr, "short write, write %d frames\n", rc);
        }

		if(left_size <= 0){
			lseek(fd, sizeof(hdr), SEEK_SET);
			totle_size = 0;
			printf("again \n");
//			read(fd, &hdr, sizeof(hdr));				
		}
    }

	fprintf(stderr, "closing device \n");
	snd_pcm_drop(handle);
    fprintf(stderr, "4 \n");
    snd_pcm_drain(handle);
	fprintf(stderr, "3 \n");
    snd_pcm_close(handle);
	fprintf(stderr, "2 \n");
	
	if(params)
	{
		snd_pcm_hw_params_free(params);
	}
	
	fprintf(stderr, "1 \n");
    free(buffer);
	
	fprintf(stderr, "exit \n");

    return 0;
}

/**************************************************************/
int play_wav(const char *fn)
{
    unsigned rate, channels;
    int fd;

    fd = open(fn, O_RDONLY, 0777);
    if (fd < 0) {
        fprintf(stderr, "playback: cannot open '%s'\n", fn);
        return -1;
    }

	/*
    if (read(fd, &hdr, sizeof(hdr)) != sizeof(hdr)) {
        fprintf(stderr, "playback: cannot read header\n");
        return -1;
    }:*/
	
	//hdr.num_channels = 2;
	//hdr.sample_rate = 44100;
	hdr.num_channels = CHANNEL;
	hdr.sample_rate = RATE;
	hdr.bits_per_sample = 16;
	hdr.audio_format = FORMAT_PCM;
	hdr.data_sz = GetSFileize(fn);
	
	#ifdef INTERLEAVED
    fprintf(stderr,"playback: %d ch, %d hz, %d bit, %s, %s, file_size %ld\n",
            hdr.num_channels, (int)hdr.sample_rate, hdr.bits_per_sample, "INTERLEAVED",
            hdr.audio_format == FORMAT_PCM ? "PCM":"unknown", hdr.data_sz);
	#else
    fprintf(stderr,"playback: %d ch, %d hz, %d bit, %s, %s, file_size %ld\n",
            hdr.num_channels, (int)hdr.sample_rate, hdr.bits_per_sample, "NON-INTERLEAVED",
            hdr.audio_format == FORMAT_PCM ? "PCM":"unknown", hdr.data_sz);	
	#endif

    return playback_file(hdr.sample_rate, hdr.num_channels, fd, hdr.data_sz);
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr,"usage: playback <file>\n");
       // return -1;
    }

    return play_wav(argv[1]);
	
}
