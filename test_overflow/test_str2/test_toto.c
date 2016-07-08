
//#define TEST_JMP
//#define TEST_SYS
//#define TEST_MEMCPY
//#define TEST_ALIGNMENT
#define TEST_VOID

#ifdef TEST_JMP
#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;

void banana()
{
    printf("ready to go\n");
    longjmp(buf, 5);
    printf("you're dead! \n");
}

int main(int argc, char **argv)
{
        int ret = 0;
        volatile int i;
         
        printf("start\n");

        i = 0;
        ret = setjmp(buf);
        printf("ret = %d\n", ret);
        printf("i = %d\n", i++);
        
        if(ret == 5)
            {
            printf("back to main \n");
            }
        else
            {
            printf("first time\n");
            banana();
            }

        printf("end\n");
        
        return 0;
}
#endif

#ifdef TEST_SYS
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

using namespace std;

void call_script(string command)
{
	system(command.c_str());
}

string ReadOutputCommand (string command)
{
	#ifdef _WIN32
	#define popen _popen
	#define pclose _pclose
	#endif

	#define MAX_RES_BUF 10000

	FILE *fp;
	int status;
	char buf[MAX_RES_BUF];

	fp = popen(command.c_str(), "r");
	if (fp == NULL)
	{
		return "Cannot execute command";
	}
	
	stringstream response;
	while (fgets(buf, MAX_RES_BUF, fp) != NULL)
	{
		response << buf;
	}

	if(fp)
	{
		status = pclose(fp);
	}

	return response.str();
}

string call_script(void);

int main(void)
{
    string str=ReadOutputCommand("./test_echo.sh");
    cout << "popen:" << str << endl;
    
    call_script("./test_echo.sh");


    return 0;
}
#endif

#ifdef TEST_MEMCPY
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MARGINAL 65536

#define DUMBCOPY for(i=0;i<MARGINAL;i++) \
                destination[i] = source[i];

#define SMARTCOPY memcpy(destination, source, MARGINAL)

main()
{
    struct timeval tv1, tv2;
    char source[MARGINAL], destination[MARGINAL];
    unsigned int i,j;

    for(j=0;j<MARGINAL-1;j++)
           source[j]=j;

    gettimeofday(&tv1, NULL);

   
    for(j=0;j<100;j++) {
           //SMARTCOPY;
           DUMBCOPY
        }
    
    gettimeofday(&tv2, NULL);

    printf("time interval : %dusec %dms\n", tv2.tv_sec - tv1.tv_sec, (tv2.tv_usec - tv1.tv_usec)/1000 );
   
}

#endif

#ifdef TEST_ALIGNMENT
#include <stdio.h>



main()
{
    union {
        char a[10];
        int i;
        }u;

    int *p = (int*)&(u.a[1]);
    *p = 17;

    char c = 9;
    foo(c);
   

}


#endif

#ifdef TEST_VOID
#include <iostream>


using namespace std;

class CBase
{
    public:
        void func() { cout << "CBase::func" << endl;}
    private:
        int a;
};


int main()
{
    void *p = new CBase();
    //((CBase*)p)->func();
    static_cast<CBase *>(p)->func();
}


#endif
