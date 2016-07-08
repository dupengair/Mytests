#ifndef RATIONAL_H
#define RATIONAL_H

//class ByteMemoryPool;
#include "ByteMemoryPool.h"

class Rational {
public:
    Rational (int a = 0, int b = 1) : n(a), a(b) {}

    void *operator new(size_t size) { return memPool->alloc(size); }
    void operator delete(void *doomed, size_t size) { memPool->free(doomed); }

    static void newMemPool() { memPool = new ByteMemoryPool; }
    static void deleteMemPool() { delete memPool; }

private:
    int n;
    int a;

    static ByteMemoryPool *memPool;
};

#endif
