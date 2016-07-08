#include <sys/time.h>
#include <unistd.h>

#include <iostream>

using std::cout;
using std::endl;


class GetTimeElapsed {
    private:
        struct timeval tv1;
        struct timeval tv2;

        void StartTimeCount(void) {
            gettimeofday(&tv1, NULL);
        }

        void EndTimeCount(void) {          
            gettimeofday(&tv2, NULL);
        }
            
        void PrintTime(void) {
            cout << "time elapsed: " << (tv2.tv_sec - tv1.tv_sec) << " s, " 
                                                << (tv2.tv_usec - tv1.tv_usec) / 1000 << " ms, " 
                                                << (tv2.tv_usec - tv1.tv_usec) << " us" 
                                                <<endl;
        }

    public:
        GetTimeElapsed() { 
            StartTimeCount(); 
        }
        
        ~GetTimeElapsed() {
            EndTimeCount();
            PrintTime();
        }


};

#define STARTCOUNT { GetTimeElapsed timer
#define ENDCOUNT }
