/*
This example reads from the default PCM device
and writes to standard output for 5 seconds of data.
*/ 

/* Use the newer ALSA API */
#define ALSA_PCM_NEW_HW_PARAMS_API 

#include <alsa/asoundlib.h>
#include <unistd.h>
#include <sys/time.h>

#define RATE 8000
#define CHANNEL 1
#define INTERLEAVED  
#define LOOPTIME 5 //seconds
//#define HAVE_MIXER
#define TEST_TIME


#ifdef HAVE_MIXER

	#include <math.h>
	#include <ctype.h>
	#include <string>
	
	using std::string;


	static int no_check = 0;
	//static int debugflag = 0;

	#define convert_prange1(val, min, max) \
		ceil((val) * ((max) - (min)) * 0.01 + (min))
	#define check_range(val, min, max) \
		(no_check ? (val) : ((val < min) ? (min) : (val > max) ? (max) : (val))) 

	enum { VOL_RAW, VOL_DB };

	typedef struct channel_mask 
	{
		char *name;
		unsigned int mask;
	} channel_mask_t;
	
	static const channel_mask_t chanmask[] = {
		{(char*)"frontleft", 1 << SND_MIXER_SCHN_FRONT_LEFT},
		{(char*)"frontright", 1 << SND_MIXER_SCHN_FRONT_RIGHT},
		{(char*)"frontcenter", 1 << SND_MIXER_SCHN_FRONT_CENTER},
		{(char*)"front", ((1 << SND_MIXER_SCHN_FRONT_LEFT) |
			   (1 << SND_MIXER_SCHN_FRONT_RIGHT))},
		{(char*)"center", 1 << SND_MIXER_SCHN_FRONT_CENTER},
		{(char*)"rearleft", 1 << SND_MIXER_SCHN_REAR_LEFT},
		{(char*)"rearright", 1 << SND_MIXER_SCHN_REAR_RIGHT},
		{(char*)"rear", ((1 << SND_MIXER_SCHN_REAR_LEFT) |
			  (1 << SND_MIXER_SCHN_REAR_RIGHT))},
		{(char*)"woofer", 1 << SND_MIXER_SCHN_WOOFER},
		{NULL, 0}
	};
	
	

	int set_playback_dB(snd_mixer_elem_t *elem, snd_mixer_selem_channel_id_t c, long value)
	{
		return snd_mixer_selem_set_playback_dB(elem, c, value, 0);
	}

	int set_capture_dB(snd_mixer_elem_t *elem, snd_mixer_selem_channel_id_t c, long value)
	{
		return snd_mixer_selem_set_capture_dB(elem, c, value, 0);
	}

	
	struct volume_data 
	{
		int (*get_range)(snd_mixer_elem_t *elem, long *min, long *max);
		int (*get)(snd_mixer_elem_t *elem, snd_mixer_selem_channel_id_t c, long *value);
		int (*set)(snd_mixer_elem_t *elem, snd_mixer_selem_channel_id_t c, long value);
	};
	

	struct volume_data_set 
	{
		int (*has_volume)(snd_mixer_elem_t *elem);
		struct volume_data v[2];
	};
	
	struct volume_data_set vol_data[2] =
	{
		{ snd_mixer_selem_has_playback_volume, { 
			{snd_mixer_selem_get_playback_volume_range, snd_mixer_selem_get_playback_volume, snd_mixer_selem_set_playback_volume}, 
			{snd_mixer_selem_get_playback_dB_range, snd_mixer_selem_get_playback_dB, set_playback_dB} } 
		},
		{ snd_mixer_selem_has_capture_volume, { 
			{snd_mixer_selem_get_capture_volume_range, snd_mixer_selem_get_capture_volume, snd_mixer_selem_set_capture_volume},
			{snd_mixer_selem_get_capture_dB_range, snd_mixer_selem_get_capture_dB, set_capture_dB} } 
		}
	};
	
	
	int parse_simple_id(const char *str, snd_mixer_selem_id_t *sid)
	{
		char buf[128];
		char *ptr = buf;

		while ((*str) == ' ' || (*str) == '\t')
			str++;
		if ((*str) == 0)
			return -EINVAL;
			
		int size = 1;
		if ((*str) != '"' && (*str) != '\'') 
		{
			while ((*str) && (*str) != ',') 
			{
				if (size < (int)sizeof(buf)) 
				{
					*ptr++ = (*str);
					size++;
				}
				str++;
			}
		} 
		else 
		{
			int c = *str++;
			while ((*str) && (*str) != c) 
			{
				if (size < (int)sizeof(buf)) 
				{
					*ptr++ = (*str);
					size++;
				}
				str++;
			}
			if ((*str) == c)
				str++;
		}
		if ((*str) == '\0') 
		{
			snd_mixer_selem_id_set_index(sid, 0);
			*ptr = 0;
			
			snd_mixer_selem_id_set_name(sid, buf);
			return 0;
		}
		if ((*str) != ',')
			return -EINVAL;
			
		*ptr = 0;
		str++;
		if (!isdigit(*str))
			return -EINVAL;
			
		snd_mixer_selem_id_set_index(sid, atoi(str));
		snd_mixer_selem_id_set_name(sid, buf);
		
		return 0;
	}

	unsigned int channels_mask(char **arg, unsigned int def)
	{
		const channel_mask_t *c;

		for (c = chanmask; c->name; c++) 
		{
			if (strncasecmp(*arg, c->name, strlen(c->name)) == 0) 
			{
				while (**arg != '\0' && **arg != ',' && **arg != ' ' && **arg != '\t')
					(*arg)++;
				if (**arg == ',' || **arg == ' ' || **arg == '\t')
					(*arg)++;
				return c->mask;
			}
		}
		return def;
	}

	unsigned int dir_mask(char **arg, unsigned int def)
	{
		int findend = 0;

		if (strncasecmp(*arg, "playback", 8) == 0)
			def = findend = 1;
		else if (strncasecmp(*arg, "capture", 8) == 0)
			def = findend = 2;
		if (findend) 
		{
			while (**arg != '\0' && **arg != ',' && **arg != ' ' && **arg != '\t')
				(*arg)++;
			if (**arg == ',' || **arg == ' ' || **arg == '\t')
				(*arg)++;
		}
		return def;
	}
	
		int get_bool_simple(char **ptr, char *str, int invert, int orig)
	{
		if (**ptr == ':')
			(*ptr)++;
		if (!strncasecmp(*ptr, str, strlen(str))) 
		{
			orig = 1 ^ (invert ? 1 : 0);
			while (**ptr != '\0' && **ptr != ',' && **ptr != ':')
				(*ptr)++;
		}
		if (**ptr == ',' || **ptr == ':')
			(*ptr)++;
		return orig;
	}
		
	int simple_skip_word(char **ptr, char *str)
	{
		char *xptr = *ptr;
		if (*xptr == ':')
			xptr++;
		if (!strncasecmp(xptr, str, strlen(str))) 
		{
			while (*xptr != '\0' && *xptr != ',' && *xptr != ':')
				xptr++;
			if (*xptr == ',' || *xptr == ':')
				xptr++;
			*ptr = xptr;
			return 1;
		}
		return 0;
	}

	int set_volume_simple(snd_mixer_elem_t *elem, snd_mixer_selem_channel_id_t chn, char **ptr, int dir)
	{
		int invalid = 0;
		int err = 0;
		int vol_type = VOL_RAW;

		if (!vol_data[dir].has_volume(elem))
			invalid = 1;

		char *p = *ptr;
		if ((*p) == ':')
			p++;
			
		if ((*p) == '\0' || (!isdigit(*p) && (*p) != '-'))
		{
			if ((*p) == ',')
				p++;
			*ptr = p;
			
			if (err)
				return err;
			else if (invalid)
				return -ENOENT;
			else
			 return 0;
		}

		long orig, pmin, pmax;
		if (!invalid && vol_data[dir].v[VOL_RAW].get_range(elem, &pmin, &pmax) < 0)
			invalid = 1;

		char* s = p;
		long val = strtol(s, &p, 10);
		if ((*p) == '.')
		{
			p++;
			strtol(p, &p, 10);
		}
		
		if ((*p) == '%') 
		{
			if (! invalid)
				val = (long)convert_prange1(strtod(s, NULL), pmin, pmax);
				
			p++;
		} 
		else if (p[0] == 'd' && p[1] == 'B') 
		{
			if (! invalid) 
			{
				val = (long)(strtod(s, NULL) * 100.0);
				vol_type = VOL_DB;
				
				if (vol_data[dir].v[vol_type].get_range(elem, &pmin, &pmax) < 0)
					invalid = 1;
			}
			p += 2;
		}
		
		if ((*p) == '+' || (*p) == '-') 
		{
			if (! invalid) 
			{
				if (vol_data[dir].v[vol_type].get(elem, chn, &orig) < 0)
					invalid = 1;
					
				if ((*p) == '+')
					val = orig + val;
				else
					val = orig - val;
			}
			p++;
		}
		
		if (! invalid) 
		{
			val = check_range(val, pmin, pmax);
			err = vol_data[dir].v[vol_type].set(elem, chn, val);
		}

		if ((*p) == ',')
			p++;
			
		*ptr = p;
		
		return err ? err : (invalid ? -ENOENT : 0);
	}				
	

	
	int sset_channels(snd_mixer_elem_t *elem, unsigned int argc, char **argv)
	{
		int check_flag = -1;
		unsigned int dir = 3;
		unsigned int okflag = 3;
		unsigned int channels = ~0U;

		for (unsigned int idx = 0; idx < argc; idx++) 
		{
			char *ptr = argv[idx];
			int firstchn = 1;
			
			channels = channels_mask(&ptr, channels);
			if (*ptr == '\0')
				continue;
				
			dir = dir_mask(&ptr, dir);
			if (*ptr == '\0')
				continue;
				
			int multi = (strchr(ptr, ',') != NULL);
			char* optr = ptr;
			for (int i = 0; i <= SND_MIXER_SCHN_LAST; i++) 
			{
				snd_mixer_selem_channel_id_t chn = (snd_mixer_selem_channel_id_t)i;
				char *sptr = NULL;
				int ival;
				
				if (!(channels & (1 << chn)))
					continue;

				if ((dir & 1) && snd_mixer_selem_has_playback_channel(elem, chn)) 
				{
					sptr = ptr;
					
					if (!strncmp(ptr, "on", 2) && snd_mixer_selem_has_playback_switch(elem)) 
					{
						snd_mixer_selem_get_playback_switch(elem, chn, &ival);
						if (snd_mixer_selem_set_playback_switch(elem, chn, get_bool_simple(&ptr, (char*)"on", 0, ival)) >= 0)
							check_flag = 1;
					} 
					else if (!strncmp(ptr, "off", 3) && snd_mixer_selem_has_playback_switch(elem)) 
					{
						snd_mixer_selem_get_playback_switch(elem, chn, &ival);
						if (snd_mixer_selem_set_playback_switch(elem, chn, get_bool_simple(&ptr, (char*)"off", 1, ival)) >= 0)
							check_flag = 1;
					} 
					else if (!strncmp(ptr, "mute", 4) && snd_mixer_selem_has_playback_switch(elem)) 
					{
						snd_mixer_selem_get_playback_switch(elem, chn, &ival);
						if (snd_mixer_selem_set_playback_switch(elem, chn, get_bool_simple(&ptr, (char*)"mute", 1, ival)) >= 0)
							check_flag = 1;
					} 
					else if (!strncmp(ptr, "unmute", 6) && snd_mixer_selem_has_playback_switch(elem)) 
					{
						snd_mixer_selem_get_playback_switch(elem, chn, &ival);
						if (snd_mixer_selem_set_playback_switch(elem, chn, get_bool_simple(&ptr, (char*)"unmute", 0, ival)) >= 0)
							check_flag = 1;
					} 
					else if (!strncmp(ptr, "toggle", 6) && snd_mixer_selem_has_playback_switch(elem)) 
					{
						if (firstchn || !snd_mixer_selem_has_playback_switch_joined(elem)) 
						{
							snd_mixer_selem_get_playback_switch(elem, chn, &ival);
							if (snd_mixer_selem_set_playback_switch(elem, chn, (ival ? 1 : 0) ^ 1) >= 0)
								check_flag = 1;
						}
						simple_skip_word(&ptr, (char*)"toggle");
					} 
					else if (isdigit(*ptr) || *ptr == '-' || *ptr == '+') 
					{
						if (set_volume_simple(elem, chn, &ptr, 0) >= 0)
							check_flag = 1;
					} 
					else if (!(simple_skip_word(&ptr, (char*)"cap") || simple_skip_word(&ptr, (char*)"rec") ||
						   simple_skip_word(&ptr, (char*)"nocap") || simple_skip_word(&ptr, (char*)"norec")))
					{
						okflag &= ~1;
					}
				}
				
				if ((dir & 2) && snd_mixer_selem_has_capture_channel(elem, chn)) 
				{
					if (sptr != NULL)
						ptr = sptr;
					sptr = ptr;
					
					if (!strncmp(ptr, "cap", 3) && snd_mixer_selem_has_capture_switch(elem)) 
					{
						snd_mixer_selem_get_capture_switch(elem, chn, &ival);
						if (snd_mixer_selem_set_capture_switch(elem, chn, get_bool_simple(&ptr, (char*)"cap", 0, ival)) >= 0)
							check_flag = 1;
					}
					else if (!strncmp(ptr, "nocap", 5) && snd_mixer_selem_has_capture_switch(elem))
					{
						snd_mixer_selem_get_capture_switch(elem, chn, &ival);
						if (snd_mixer_selem_set_capture_switch(elem, chn, get_bool_simple(&ptr, (char*)"nocap", 1, ival)) >= 0)
							check_flag = 1;
					} 
					else if (!strncmp(ptr, "rec", 3) && snd_mixer_selem_has_capture_switch(elem)) 
					{
						snd_mixer_selem_get_capture_switch(elem, chn, &ival);
						if (snd_mixer_selem_set_capture_switch(elem, chn, get_bool_simple(&ptr, (char*)"rec", 0, ival)) >= 0)
							check_flag = 1;
					} 
					else if (!strncmp(ptr, "norec", 5) && snd_mixer_selem_has_capture_switch(elem)) 
					{
						snd_mixer_selem_get_capture_switch(elem, chn, &ival);
						if (snd_mixer_selem_set_capture_switch(elem, chn, get_bool_simple(&ptr, (char*)"norec", 1, ival)) >= 0)
							check_flag = 1;
					} 
					else if (!strncmp(ptr, "toggle", 6) && snd_mixer_selem_has_capture_switch(elem)) 
					{
						if (firstchn || !snd_mixer_selem_has_capture_switch_joined(elem))
						{
							snd_mixer_selem_get_capture_switch(elem, chn, &ival);
							if (snd_mixer_selem_set_capture_switch(elem, chn, (ival ? 1 : 0) ^ 1) >= 0)
								check_flag = 1;
						}
						simple_skip_word(&ptr, (char*)"toggle");
					} 
					else if (isdigit(*ptr) || *ptr == '-' || *ptr == '+') 
					{
						if (set_volume_simple(elem, chn, &ptr, 1) >= 0)
							check_flag = 1;
					} 
					else if (!(simple_skip_word(&ptr, (char*)"mute") || simple_skip_word(&ptr, (char*)"off") ||
						   			 simple_skip_word(&ptr, (char*)"unmute") || simple_skip_word(&ptr, (char*)"on")))
					{
						okflag &= ~2;
					}
				}
				
				if (okflag == 0) 
					return 0;
				
				if (!multi)
					ptr = optr;
					
				firstchn = 0;
			}
		}
		
		return check_flag;
	}

	bool alsa_set_control_volume(string card, string name, string volume)
	{
		int err = 0;
		snd_mixer_t *handle = NULL;
		snd_mixer_elem_t *elem;
		snd_mixer_selem_id_t *sid;
		snd_mixer_selem_id_alloca(&sid);
		
		err = parse_simple_id(name.c_str(), sid);
		if (err)
		{
			fprintf(stderr, "Wrong scontrol identifier: %s", name.c_str());
			return false;
		}
	
		err = snd_mixer_open(&handle, 0);
		if (err < 0)
		{
			fprintf(stderr, "Mixer %s open error: %s", card.c_str(), snd_strerror(err));
			return false;
		}
		
		err = snd_mixer_attach(handle, card.c_str());
		if (err < 0)
		{
			fprintf(stderr, "Mixer attach %s error: %s", card.c_str(), snd_strerror(err));
			snd_mixer_close(handle);
			return false;
		}
		
		err = snd_mixer_selem_register(handle, NULL, NULL);
		if (err < 0)
		{
			fprintf(stderr, "Mixer register error: %s", snd_strerror(err));
			snd_mixer_close(handle);
			return false;
		}
		
		err = snd_mixer_load(handle);
		if (err < 0)
		{
			fprintf(stderr, "Mixer %s load error: %s", card.c_str(), snd_strerror(err));
			snd_mixer_close(handle);
			return false;
		}
		
		elem = snd_mixer_find_selem(handle, sid);
		if (!elem)
		{
			fprintf(stderr, "Unable to find simple control '%s',%i", snd_mixer_selem_id_get_name(sid), snd_mixer_selem_id_get_index(sid));
			snd_mixer_close(handle);
			return false;
		}
		
		char* Tmp[1];
		Tmp[0] = (char*)malloc(16);
		memset(Tmp[0], 0, 16);
		strncpy(Tmp[0], volume.c_str(), 15);
		err = sset_channels(elem, 1, Tmp);
		free(Tmp[0]);
		
		if (err < 0)
		{
			fprintf(stderr, "Cmd error: %s [%s]", snd_strerror(err), volume.c_str());
			snd_mixer_close(handle);
			return false;
		}		
		
		snd_mixer_close(handle);
		
		return true;
	}
#endif

int main() {
  long loops;
  int rc;
  int size;
  snd_pcm_t *handle;
  snd_pcm_hw_params_t *params = NULL;
  unsigned int val;
  #ifdef INTEL
  int dir;
  #endif
  snd_pcm_uframes_t frames;
  char *buffer; 


  /* Open PCM device for recording (capture). */
  rc = snd_pcm_open(&handle, "default", SND_PCM_STREAM_CAPTURE, 0);
  if (rc <0 ) {    
	fprintf(stderr, "unable to open pcm device: %s\n", snd_strerror(rc));
	exit(1);
  } 

  /* Allocate a hardware parameters object. */
  rc = snd_pcm_hw_params_malloc(&params);
	if (rc < 0)
				{
					fprintf(stderr, "snd_pcm_hw_params_malloc: %s\n", snd_strerror(rc));
					exit(1);
   				}
				
  /* Fill it in with default values. */
  rc = snd_pcm_hw_params_any(handle, params); 
	if (rc < 0)
				{
					fprintf(stderr, "snd_pcm_hw_params_any: %s\n", snd_strerror(rc));
					exit(1);
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
					fprintf(stderr, "snd_pcm_hw_params_set_access: %s\n", snd_strerror(rc));
					//exit(1);
   				}
				
  /* Signed 16-bit little-endian format */
	rc = snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE); 
	if (rc < 0)
				{
					fprintf(stderr, "snd_pcm_hw_params_set_format: %s\n", snd_strerror(rc));
					exit(1);
   				}
				
  /* Two channels (stereo) */
	rc = snd_pcm_hw_params_set_channels(handle, params, CHANNEL); 
	if (rc < 0)
				{
					fprintf(stderr, "snd_pcm_hw_params_set_channels: %s\n", snd_strerror(rc));
					exit(1);
   				}
			
  /* 44100 bits/second sampling rate (CD quality) */
  val = RATE;
  #ifdef INTEL
  snd_pcm_hw_params_set_rate_near(handle, params, &val, &dir); 
  #else
  snd_pcm_hw_params_set_rate_near(handle, params, &val, 0);
  #endif
				
  /* Set period size to 32 frames. */
  frames = 256;
  #ifdef INTEL
  snd_pcm_hw_params_set_period_size_near(handle, params, &frames, &dir); 
  #else
  snd_pcm_hw_params_set_period_size_near(handle, params, &frames, 0); 
  #endif

				
  /* Write the parameters to the driver */
  rc = snd_pcm_hw_params(handle, params);
  if (rc <0 )  { 
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
 
				
  size = frames * 16 / 8 * CHANNEL; /* 2 bytes/sample, 2 channels */
  buffer = (char *) malloc(size); 

  /* We want to loop for 5 seconds */
  #ifdef INTEL
  snd_pcm_hw_params_get_period_time(params, &val, &dir);
  #else
  snd_pcm_hw_params_get_period_time(params, &val, 0);
  #endif
  fprintf(stderr, "get period time: %d\n", val);
  
  loops = LOOPTIME * 1000000 / val; 
  fprintf(stderr, "loops: %d\n", loops);
  
  #ifdef HAVE_MIXER
  alsa_set_control_volume("default", "ADC,0", "80%");
  #endif

  while (loops > 0) {
    loops--;
	
	if(RATE > 8000) {
		if(loops%1000 == 0) {
		fprintf(stderr, "loops = %ld \n", loops);
		}
	}
	else {
		if(loops%100 == 0) {
		fprintf(stderr, "loops = %ld \n", loops);
		}
	}
	
	#ifdef INTERLEAVED
	fprintf(stderr, "loops.............1\n");
    rc = snd_pcm_readi(handle, buffer, frames);
	fprintf(stderr, "loops.............2\n");
	#else
	rc = snd_pcm_readn(handle, (void **)buffer, frames);
	#endif
	
	#ifdef TEST_TIME
	static long lasttime = 0;
	struct timeval tv;		
	gettimeofday(&tv, NULL);	
	fprintf(stderr, "size = %d, interval time = %d\n", (int)frames, (tv.tv_sec *1000 + tv.tv_usec/1000-lasttime));	
	lasttime = tv.tv_sec *1000 + tv.tv_usec/1000;
	#endif

    if (rc == -EPIPE) {
      /* EPIPE means overrun */
      fprintf(stderr, "overrun occurred\n");
      snd_pcm_prepare(handle);
    } else if (rc <0) {
		fprintf(stderr, "error from read: %s\n", snd_strerror(rc));
    } else if (rc != (int)frames) {
      fprintf(stderr, "short read, read %d frames\n", rc);
    }
	
    rc = write(1, buffer, size);
    if (rc != size)
      fprintf(stderr, "short write: wrote %d bytes\n", rc);
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

  
  #ifdef INTERLEAVED
  fprintf(stderr, "captured: %d ch, %d hz, %d bit, %s\n", CHANNEL, RATE, 16, "INTERLEAVED");
  #else
  fprintf(stderr, "captured: %d ch, %d hz, %d bit, %s\n", CHANNEL, RATE, 16, "NON-INTERLEAVED");
  #endif


  return 0;
}

