#include <Rational.h>


NextOnFreeList *Rational::freeList = 0;

inline void * Rational::operator new(size_t size)
{
    if ( 0 == freeList ) {
            expandTheFreeList();
        }

    NextOnFreeList *head = freeList;
    freeList = head->next;

    return head;
}

inline void Rational::operator delete(void *doomed, size_t size)
{
    NextOnFreeList *head = static_cast<NextOnFreeList * > (doomed);

    head->next = freeList;
    freeList = head;
}

void Rational::expandTheFreeList()
{
    size_t size = (sizeof(Rational) > sizeof(NextOnFreeList *)) ? sizeof(Rational) : sizeof(NextOnFreeList);

    NextOnFreeList *runner = reinterpret_cast<NextOnFreeList *> (new char [size]);

    freeList = runner;
    for(int i = 0; i< EXPANSION_SIZE; i++)
        {
        runner->next = reinterpret_cast<NextOnFreeList *> (new char [size]);
        runner = runner->next;
        }
    
    runner->next = 0;
}

void Rational::deleteMemPool()
{
    NextOnFreeList *nextPtr;
    for(nextPtr = freeList; nextPtr != NULL; nextPtr = freeList)
        {
        freeList = freeList->next;
        delete [] nextPtr;
        }
}
