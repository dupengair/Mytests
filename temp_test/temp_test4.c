#include <semaphore.h>
#include <sys/time.h>
#include <unistd.h>
#include <thread>

//#define USE_SEM_EVENT

#ifdef USE_SEM_EVENT
sem_t sem;
#else
pthread_cond_t sig;
pthread_mutex_t mtx;
#endif

void init()
{
    #ifdef USE_SEM_EVENT
    sem_init(&sem, 0, 0);
    #else
    pthread_cond_init(&sig, NULL);
    pthread_mutex_init(&mtx, NULL);
    #endif
}

void destroy()
{
    #ifdef USE_SEM_EVENT
    sem_destroy(&sem);
    #else
    pthread_cond_destroy(&sig);
    pthread_mutex_destroy(&mtx);
    #endif
}

void post(int t)
{
    struct timeval tv, tv1;
    gettimeofday(&tv, NULL);
    #ifdef USE_SEM_EVENT
    sem_post(&sem);
    #else
    pthread_mutex_lock(&mtx);
    pthread_cond_signal(&sig);
    pthread_mutex_unlock(&mtx);
    #endif
    gettimeofday(&tv1, NULL);
    printf("time post: %d sec, %d usec\n", tv1.tv_sec-tv.tv_sec, tv1.tv_usec-tv.tv_usec);
}

void wait(int t)
{  
    struct timeval tv, tv1;
    struct timespec to;
    gettimeofday(&tv, NULL);      
    to.tv_sec = tv.tv_sec + 10;
    to.tv_nsec = tv.tv_usec * 1000;    
    #ifdef USE_SEM_EVENT
    sem_timedwait(&sem, &to);
    #else
    pthread_mutex_lock(&mtx);
    pthread_cond_timedwait(&sig, &mtx, &to);
    pthread_mutex_unlock(&mtx);
    #endif
    gettimeofday(&tv1, NULL);
    printf("time wait: %d sec, %d usec\n", tv1.tv_sec-tv.tv_sec, tv1.tv_usec-tv.tv_usec);   
}

int main()
{    
    init();
    
    std::thread t1(wait, 0);    
    sleep(1);
    std::thread t2(post, 0);
    

    t1.join();
    t2.join();

    destroy();    
}
