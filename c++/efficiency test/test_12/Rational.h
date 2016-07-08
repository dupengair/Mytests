#ifndef RATIONAL_H
#define RATIONAL_H
#include <stdlib.h>

class NextOnFreeList {
public:
    NextOnFreeList *next;
};        


class Rational {
public:
        Rational (int a = 0, int b = 1) : n(a), d(b) {}

        inline void *operator new(size_t size);
        inline void operator delete(void *doomed, size_t size);

        static void newMemPool() { expandTheFreeList(); }
        static void deleteMemPool();

private:
        static NextOnFreeList *freeList;

        static void expandTheFreeList();
        enum { EXPANSION_SIZE = 32 };

        int n;
        int d;
        
};

#endif // RATIONAL_H
