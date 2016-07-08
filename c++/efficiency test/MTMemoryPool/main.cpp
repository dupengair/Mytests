#include <iostream>
#include <Rational.h>
#include <sys/time.h>

using namespace std;

MTMemoryPool<MemoryPool<Rational>, MutexLock> * Rational::memPool = 0;

long GetTimeMS()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);

    return tv.tv_sec * 1000 + tv.tv_usec/1000; 
}

int main()
{
    cout << "start allocating..." << endl;

    Rational *array[1000];
    Rational::newMemPool();

    cout << "start calculating..." << endl;

    long startT = GetTimeMS();

    for(int j = 0; j < 500; j++) {
        for(int i = 0; i < 1000; i++) {
            array[i] = new Rational(i);
            }

        for(int k = 0; k < 1000; k++) {
            delete array[k];
            }        
        }

    cout << "end calculating...  time consuming : " << GetTimeMS() - startT << " . delete mem pool" << endl;
    
    Rational::deleteMemPool();   

    cout << "exit..." << endl;
          
}

