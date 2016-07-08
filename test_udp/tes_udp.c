#include <stdio.h>
#include <signal.h>
//#include <unistd.h>
//#include <fcntl.h>
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <netdb.h>
#include <errno.h>
//#include <stdlib.h>

#include <netinet/in.h>
//#include <netinet/ip.h>
//#include <netinet/tcp.h>
//#include <arpa/inet.h>

#define MAX_SIZE 100

char buf[MAX_SIZE*1024*1024];

int quit_flag;

static void softwdg_setQuit(void)
{
    quit_flag = 1;
}


static void sig_handle(int signo)                  
{                                                             
    if(SIGINT == signo)                             
        {                                                     
        printf("signal SIGINT. \n");                
        signal(SIGINT, SIG_IGN);
        softwdg_setQuit();
        }   
    else if(SIGKILL == signo)                    
        {                                                     
        printf("signal SIGKILL. \n");              
        signal(SIGKILL, SIG_IGN);
        softwdg_setQuit();
        }
    else if(SIGTSTP == signo)                    
        {                                                     
        printf("signal SIGTSTP. \n");              
        signal(SIGTSTP, SIG_IGN);
        softwdg_setQuit();
        }   
    else if(SIGTERM == signo)                    
        {                                                     
        printf("signal SIGTERM. \n");              
        signal(SIGTERM, SIG_IGN);
        softwdg_setQuit();
        }
    else if(SIGSEGV == signo)                    
        {                                                     
        printf("signal SIGSEGV. \n");              
        signal(SIGSEGV, SIG_IGN);
        softwdg_setQuit();
        }
    else if(SIGSYS == signo)                    
        {                                                     
        printf("signal SIGSYS. \n");              
        signal(SIGSYS, SIG_IGN);
        softwdg_setQuit();
        }

    else if(SIGABRT == signo)                    
        {                                                     
        printf("signal SIGABRT. \n");              
        signal(SIGABRT, SIG_IGN);
        softwdg_setQuit();
        }
    else if(SIGBUS == signo)                    
        {                                                     
        printf("signal SIGBUS. \n");              
        signal(SIGBUS, SIG_IGN);
        softwdg_setQuit();
        }
    else if(SIGFPE == signo)                    
        {                                                     
        printf("signal SIGFPE. \n");              
        signal(SIGFPE, SIG_IGN);
        softwdg_setQuit();
        }
    else if(SIGIO == signo)                    
        {                                                     
        printf("signal SIGIO. \n");              
        signal(SIGIO, SIG_IGN);
        softwdg_setQuit();
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
    
    if((signal(SIGSEGV, sig_handle)) == SIG_ERR)          
        {                                                                      
        perror("Failed for signal SIGSEGV ");         
        return -1; 
        }                                                                      
                                                                                    
    if((signal(SIGSYS, sig_handle)) == SIG_ERR)          
        {                                                                      
        perror("Failed for signal SIGSYS ");         
        return -1; 
        } 

    if((signal(SIGABRT, sig_handle)) == SIG_ERR)          
        {                                                                      
        perror("Failed for signal SIGABRT ");         
        return -1; 
        }  

    if((signal(SIGBUS, sig_handle)) == SIG_ERR)          
        {                                                                      
        perror("Failed for signal SIGBUS ");         
        return -1; 
        }    

    if((signal(SIGFPE, sig_handle)) == SIG_ERR)          
        {                                                                      
        perror("Failed for signal SIGFPE ");         
        return -1; 
        }                                                                      

    if((signal(SIGIO, sig_handle)) == SIG_ERR)          
        {                                                                      
        perror("Failed for signal SIGIO ");         
        return -1; 
        }         

    return 0;
}    


int main(int argc, char* argv[])
{
    unsigned long dest = 0;
    unsigned long  size = 0, num=0, i;
    int sock = -1;
    struct sockaddr_in addr_to;

    sig_match();
    quit_flag = 0;

    size = atoi(argv[1]);
    if((size < 0)||(size > MAX_SIZE))
        {
        printf("size invalid : 0 - %d [%d]\n", MAX_SIZE, size);
        return;
        }
    printf("size  :  [%d]\n", size);
    
    /* 输入的目的地址为字符串IP地址 */    
    dest = inet_addr(argv[2]);
    if(dest == INADDR_NONE)
        {
        perror("inet_addr");
        return -1;
        }
    printf("dest  :  [%s]\n", argv[2]);


    /* init buf */
    for(i=0; i<size; i++)
        {
        buf[i] = i % 255;
        }

    /* socket */
    sock = socket (AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)	   
        {
        perror("socket");
        return -1;
        }

    addr_to.sin_family = AF_INET;
    addr_to.sin_port = htons(9321);
    addr_to.sin_addr.s_addr = dest;

    /* send */
    while(quit_flag == 0)
        {
        num = sendto(sock, buf, size, 0, (struct sockaddr*)&addr_to, sizeof(addr_to));
        }

    if(sock > 0)
        {
        close(sock);
        }

    printf("quit test_udp");
    
}
