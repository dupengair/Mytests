#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void)
{
    pid_t pid;
    
	pid = fork();
	
	if (pid > 0)
	{
	    int status;
		// error ->
		
		// restore child signal before return
	//	sleep(10);
		printf("in parent\n");
    //    wait(&status);
		
        return pid;
      }
  else if (pid == 0)
    {

            int n=5;
            
		printf("in child\n");

            while(n--)
                {
              sleep(1);
              printf("in child, n =%d\n", n);
                }
    }

  printf("exit\n");
}  
