#include <pthread.h>

class MutexLock
{
    public:
        MutexLock(){
		pthread_mutex_init(&mutex_, NULL);
	}
		
        ~MutexLock() {
		pthread_mutex_destroy(&mutex_);
	}
		

	// internal usage		
        void lock() {
		pthread_mutex_lock(&mutex_);
	}
		
        void unlock() {
		pthread_mutex_unlock(&mutex_);
	}

	pthread_mutex_t mutex_;
};
class MutexLockGuard
{
    public:
        explicit MutexLockGuard(MutexLock& mutex): mutex_(mutex) {
		mutex_.lock();
	}
		
        ~MutexLockGuard() {
		mutex_.unlock();
	}
		
    private:	
        MutexLock& mutex_;
};



// Prevent misuse like:
// MutexLockGuard(mutex_);
// A tempory object doesn't hold the lock for long!
#define MutexLockGuard(x) error "Missing guard object name"
