#include "stdio.h"

//extern int *iarray;
extern int iarray[];

//extern char *carray;
extern char carray[];

//extern char *sarray;
extern char sarray[];


    

#if 1
void main()
{
    int i;
    for(i = 0; i<10; i++)
        {        
        //printf("iarray[%d] = %d\n", i, *(iarray+i)); 
        //printf("carray[%d] = %c\n", i, *(carray+i));    
        //printf("sarray[%d] = %c\n", i, *(sarray+i));
        }

    for(i = 0; i<10; i++)
        {  
        //printf("iarray[%d] = %d\n", i, iarray[i]); 
        //printf("carray[%d] = %c\n", i, carray[i]);
        //printf("sarray[%d] = %c\n", i, sarray[i]);        
        }




}
#else
#include <stdio.h>
#include <poll.h>
#include <errno.h>

int  safe_poll(struct pollfd *ufds, nfds_t nfds, int timeout)
{
	while (1) {
		int n = poll(ufds, nfds, timeout);
		if (n >= 0)
			return n;
		/* Make sure we inch towards completion */
		if (timeout > 0)
			timeout--;
		/* E.g. strace causes poll to return this */
		if (errno == EINTR)
			continue;
		/* Kernel is very low on memory. Retry. */
		/* I doubt many callers would handle this correctly! */
		if (errno == ENOMEM)
			continue;
		perror("poll");
		return n;
	}
}


void main()
{
    char buf[1024];

    puts("before open \n");
    FILE *p=popen("top -b", "r");
    struct pollfd pfd[1];



    
    if(NULL != p)
        {
        int i =0;
        puts("normal open\n");

       pfd[0].fd = fileno(p);
	pfd[0].events = POLLIN;

    int ret =safe_poll(pfd, 1, 5000);
       if( ret > 0)
        { 
        puts("could read \n");
        while(!feof(p))
            {
            printf("read %d time\n",i);
            fread(buf, sizeof(buf), 1, p);   
            puts(buf);
            
            i++;
            }
        }
       else if( ret == 0)
        {
            puts("timeout");
        }
       

        
        }
    else
        {
        printf("rpwt\n");
        }
    
}
#endif
