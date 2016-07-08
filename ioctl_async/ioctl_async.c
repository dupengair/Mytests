/***************************************************************************************
* File Name: loctl_async.c
* Description:
* Creator: dup
* Date: 2012-02-15
***************************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if_arp.h>
#include <string.h>
#include <linux/sockios.h>
#include <linux/if.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
#include <errno.h>
//#include <string.h>
#include <dirent.h>
//#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h>
#include <time.h>


#define _ERR(op, fmt, args...)        \
                    perror(op);                \
                    printf (fmt, ##args)
                    
#define NAMELENGTH 64

int live = 1;
int s  =-1;		/* socket描述符 */
struct sockaddr_in addr;

static int pickstr(char *dst, char *src, char from, char to, int n)
{
    int i = 0;
    
    while(*src++ != from)
        {
        if(*src == '\0')
            {
            return -1;
            }
        }

    
    while((i < n) && (*src != to))
        {
        if(*src == '\0')
            {
            return i;
            }

       if(*src != to)
            {
            i++;
            *dst++ = *src++; 
            }
        }

    *dst = '\0';
    return i;
}

static int getnamebypid(int pid, char *name)
{
    DIR *dp;
    FILE *fp;
    char buf[NAMELENGTH];
    int ret;

    sprintf(buf, "/proc/%d", pid);
    if((dp=opendir(buf))==NULL)
        {
        _ERR("opendir", "process pid = %d not exist\n", pid);
        return -1;
        }
    closedir(dp);

    sprintf(buf, "/proc/%d/stat", pid);
    if((fp = fopen(buf, "r")) == NULL)
        {
        _ERR("fopen", "can't open file : %s\n", buf);
        return -1;
        }
    
    if(fgets(buf,sizeof(buf),fp) == NULL)
        {

        _ERR("fgets", "read file : %s failed\n", buf);
        fclose(fp);
        ret = -1;
        }

    if(pickstr(name, buf, '(', ')', NAMELENGTH) > 0)
        {

        ret = 0;
        }

    fclose(fp);
    return ret;

}

static int getpidbyname(char *pname)
{
    FILE *fp;
    DIR *dp;
    struct dirent *dirp;
    int pid = 0;
    char buf[128];
    char *pidchar = NULL;

    if((dp = opendir("/proc")) == NULL)
        {
        _ERR("opendir", "can't read dir /proc\n");
        return -1;
        }

    while((dirp = readdir(dp)) != NULL)
        {
        pidchar = dirp->d_name;
        if((*pidchar >= '0') && (*pidchar <= '9'))
            {
            pid = atoi(pidchar);
            sprintf(buf, "/proc/%d/stat", pid);

            if((fp = fopen(buf, "r")) == NULL)
                {
                continue;
                }
            
            fread(buf, sizeof(buf), 1, fp);
            fclose(fp);
            
            if(strstr(buf, pname) == 0)
                {
                pid = 0;
                continue;
                }
            
            break;
            }
        }

    closedir(dp);
    return pid;
}


int recv_proc(const char *where)
{
	struct tm *p;
	int ret = -1;
	unsigned int n = 0;
	char recvbuff[256];
    	char *week[]={"sun","mon","tue","wed","thu","fri","sat"};

	int request = -1;/* 请求类型 */
	struct timeval tv;/* ioctl第三个参数 */
	
	memset(recvbuff, 0, sizeof(recvbuff));
	if(recvfrom(s, recvbuff,  sizeof(recvbuff), 0, (struct sockaddr *)&addr, &n) == -1){
		//perror("recvfrom");
		usleep(200000);
		}
	else
		{
		/* 获得数据报文到达的时间 */	
		request = SIOCGSTAMP;/*FIOSETOWN*/
		ret = ioctl(s, request, &tv);
		if(ret){/* ioctl函数出错 */
			/* 错误处理 */
			perror("ioctl");
		}else{
			/* 获得了最后数据报文到达时间，在参数tv内 */
			p = localtime(&tv.tv_sec);
			printf("in %s data reach time : %lds %ldus => %d-%d-%d %s %d:%d:%d \n", where, tv.tv_sec, tv.tv_usec,
			p->tm_year+1900, p->tm_mon + 1, p->tm_mday, week[p->tm_wday],
			p->tm_hour, p->tm_min, p->tm_sec);
		}
			
		printf("peer:%s\n", recvbuff);
		sleep(1);
	}

	return 0;
}


static void sig_handle(int signo)                  
{                                                             
    if(SIGINT == signo)                             
        {                                                     
        printf("signal SIGINT. \n");                
        signal(SIGINT, SIG_IGN);
	 live = 0;
        }   
    else if(SIGKILL == signo)                    
        {                                                     
        printf("signal SIGKILL. \n");              
        signal(SIGKILL, SIG_IGN);
	 live = 0;
        }
    else if(SIGTSTP == signo)                    
        {                                                     
        printf("signal SIGTSTP. \n");              
        signal(SIGTSTP, SIG_IGN);
	 live = 0;
        }   
    else if(SIGTERM == signo)                    
        {                                                     
        printf("signal SIGTERM. \n");              
        signal(SIGTERM, SIG_IGN);
	 live = 0;
        }
    else if(SIGIO == signo)                    
        {                                                     
        printf("signal SIGIO. \n");              
        //signal(SIGTERM, SIG_IGN);
        recv_proc(__func__);
	 //live = 0;
    	}
}                                                             


static int sig_match(void)                  
{  
    if((signal(SIGINT, sig_handle)) == SIG_ERR)          
        {                                                                      
        perror("Failed for signal SIGINT ");         
        return -1; 
        }    
    
    if((signal(SIGTSTP, sig_handle)) == SIG_ERR)        
        {                                                                      
        perror("Failed for signal SIGTSTP ");        
        return -1; 
        }    
    
    if((signal(SIGTERM, sig_handle)) == SIG_ERR)          
        {                                                                      
        perror("Failed for signal SIGTERM ");         
        return -1; 
        }   
	
    if((signal(SIGIO, sig_handle)) == SIG_ERR)          
        {                                                                      
        perror("Failed for signal SIGIO ");         
        return -1; 
        }    

    return 0;
}    



int main(int argc, char **argv)
{
	int err = -1;		
	int request = -1;
	int para = -1;	

	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0)	{
		perror("socket");
		return -1;
	}

	sig_match();
    
	/* 有无带外数据判断 */	
	request = SIOCATMARK;
	err = ioctl(s, request, &para);
	if(err){
	}
	if(para){ /* 有带外数据 */
		/* 接收带外数据，处理... */
		printf("have oob data\n");
	}else{/*无带外数据*/
		printf("no oob data\n");
	}
	
	
	/* 设置SIGIO和SIGURG信号处理进程ID */
	char name[NAMELENGTH];
	//para = getpidbyname("ambapp");
	//para = getpid();
	request = SIOCSPGRP;/*FIOSETOWN*/
	err = ioctl(s, request, &para);
	if(err){
		perror("ioctl");
	}else{
		/* 成功设置了处理信号的进程ID号 */
		getnamebypid(para, name);
		printf("set process %s(%d) with signal \n", name, para);
	}
	
	int on = 1;
	if(-1 == ioctl(s, FIOASYNC, &on)){
		perror("Fcntl FIOASYNC failed");
		exit(-1);		
	}    
	if(-1 == ioctl(s, FIONBIO, &on)){
		perror("ioctl FIONBIO failed");
		exit(-1);		
	}
	
	/* 获得SIGIO和SIGURG信号处理进程ID */
	para = -1;
	request = SIOCGPGRP;/*或者FIOGETOWN*/
	err = ioctl(s, request, &para);
	if(err){
		perror("ioctl");
	}else{
		/* 获得了处理信号的进程ID号 */
		memset(name, 0, sizeof(name));
		if(getnamebypid(para, name) < 0)
			{
			printf("get process name of ID : %d failed\n", para);
			}
		
		printf("get process %s(%d) with signal \n", name, para);
	}

	//raise(SIGIO);

	#if 0
	/* 获得数据报文到达的时间 */	
	request = SIOCGSTAMP;/*FIOSETOWN*/
	err = ioctl(s, request, &tv);
	if(err){/* ioctl函数出错 */
		/* 错误处理 */
		perror("ioctl");
	}else{
		/* 获得了最后数据报文到达时间，在参数tv内 */
		printf("data reach time : %lds %ldus\n", tv.tv_sec, tv.tv_usec);
	}
	#endif
	
		
	memset(&addr,0,sizeof(addr));
	addr.sin_family =  AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(50001);

	err = bind(s,(struct sockaddr *)&addr,sizeof(addr));
	if(-1 == err){
		perror("Bind socket failed");
		exit(-1);
	}	

		
	while(live){
		recv_proc(__func__);
	}	
	
	close(s);	


    return 0;
}
