#include <pthread.h>


class ABCLock {
public:
     virtual ~ABCLock() {}
     virtual void Lock() = 0;
     virtual void unLock() = 0;
};

class MutexLock: public ABCLock {
public:
     MutexLock() {pthread_mutex_init(&lock, NULL); }
     ~MutexLock() {pthread_mutex_destroy(&lock); }
     inline void Lock() {pthread_mutex_lock(&lock); }
     inline void unLock() {pthread_mutex_unlock(&lock); }
public:
    pthread_mutex_t lock;
};

