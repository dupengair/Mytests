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

#define BUFLEN 255
int live = 1;

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
    

    return 0;
}    

/******************************************************************************
 * IPaddr_GetHost_API : ��ȡ����IP ��ַ
 ******************************************************************************/
int IPaddr_GetHost_API(char *HostIP)
{
    int inet_sock;
    struct ifreq ifr;
    
    inet_sock = socket(AF_INET, SOCK_DGRAM, 0);
    strcpy(ifr.ifr_name, "eth0");
    if (ioctl(inet_sock, SIOCGIFADDR, &ifr),0)
        {
        perror("ioctl");
        return -1;
        }

    strcpy(HostIP, inet_ntoa(((struct sockaddr_in*)&(ifr.ifr_addr))->sin_addr));
    close(inet_sock);
    return 0;
}


int main(int argc, char **argv)
{
struct sockaddr_in peeraddr, myaddr;

int sockfd;
char IPaddr[16];
char recmsg[BUFLEN + 1];
unsigned int socklen;

sig_match();
	
/* ���� socket ����UDPͨѶ */
sockfd = socket(AF_INET, SOCK_DGRAM, 0);
if (sockfd < 0) {
printf("socket creating error\n");
exit(1);
}
socklen = sizeof(struct sockaddr_in);

/* ���öԷ��Ķ˿ں�IP��Ϣ */
memset(&peeraddr, 0, socklen);
peeraddr.sin_family = AF_INET;
peeraddr.sin_port = htons(50001);


if (argv[1]) {
/* ע���������õĶԷ���ַ��ָ�鲥��ַ�������ǶԷ���ʵ��IP��ַ */
if (inet_pton(AF_INET, argv[1], &peeraddr.sin_addr) <= 0) {
printf("wrong group address!\n");
exit(0);
}
} else {
printf("no address!\n");
exit(0);
}

/* �����Լ��Ķ˿ں�IP��Ϣ */
memset(&myaddr, 0, socklen);
myaddr.sin_family = AF_INET;
myaddr.sin_port = htons(23456);
myaddr.sin_addr.s_addr = INADDR_ANY;

/* ���Լ��Ķ˿ں�IP��Ϣ��socket�� */
if (bind
(sockfd, (struct sockaddr *) &myaddr,
sizeof(struct sockaddr_in)) == -1) {
printf("Bind error\n");
exit(0);
}

memset(recmsg, 0, sizeof(recmsg));
IPaddr_GetHost_API(IPaddr);
sprintf(recmsg, "from %s \n", IPaddr);
printf("start send : %s\n", recmsg);

/* ѭ�������û��������Ϣ�����鲥��Ϣ */
while (live) {
/* �����û����� */
/* ������Ϣ */
if (sendto
(sockfd, recmsg, strlen(recmsg), 0,
(struct sockaddr *) &peeraddr,
sizeof(struct sockaddr_in)) < 0) {
printf("sendto error!\n");
exit(3);
}
//printf("'%s' send ok\n", recmsg);
}

return 0;
}
