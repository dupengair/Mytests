#ifndef RATIONAL_H
#define RATIONAL_H

//class MemoryPool;
#include "MemoryPool.h"
#include "MTMemoryPool.h"
#include "ABCLock.h"

class Rational {
public:
    Rational (int a = 0, int b = 1) : n(a), a(b) {}

    void *operator new(size_t size) { return memPool->alloc(size); }
    void operator delete(void *doomed, size_t size) { memPool->free(doomed); }

    static void newMemPool() { memPool = new MTMemoryPool<MemoryPool <Rational>, MutexLock>; }
    static void deleteMemPool() { delete memPool; }

private:
    int n;
    int a;

    static MTMemoryPool<MemoryPool<Rational>, MutexLock> *memPool;
};

#endif
