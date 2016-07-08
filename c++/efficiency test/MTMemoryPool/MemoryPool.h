
template< class T >
class MemoryPool {
public:
    MemoryPool (size_t size = EXPANSION_SIZE);
    ~MemoryPool();

    inline void* alloc (size_t size);
    inline void free(void *someElement);
private:
    MemoryPool<T>* next;
    enum { EXPANSION_SIZE = 32 };
    void expandTheFreeList(int howMany = EXPANSION_SIZE);
};

template< class T>
MemoryPool<T>::MemoryPool(size_t size)
{
    expandTheFreeList(size);
}

template< class T>
MemoryPool<T>::~MemoryPool()
{
    MemoryPool<T> *nextPtr = next;
    for(nextPtr = next; nextPtr != NULL; nextPtr = next) {
        next = next->next;
        delete [] nextPtr;
        }
}

template< class T>
void* MemoryPool<T>::alloc(size_t)
{
    if(!next) {
        expandTheFreeList();
        }

    MemoryPool<T> *head = next;
    next = head->next;

    return head;
}

template< class T>
void MemoryPool<T>::free(void *doomed)
{
    MemoryPool<T>* head = reinterpret_cast<MemoryPool<T>* >(doomed);

    head->next = next;
    next = head;
}

template< class T>
void MemoryPool<T>::expandTheFreeList(int howMany)
{
    size_t size = (sizeof(T) > sizeof (MemoryPool<T>*)) ? sizeof(T) : sizeof(MemoryPool<T>*);
    MemoryPool *runner = reinterpret_cast<MemoryPool<T>* >(new char [size]);

    next = runner;
    for(int i=0; i<howMany; i++) {
        runner->next = reinterpret_cast<MemoryPool<T>* >(new char [size]);
        runner = runner->next;
        }

    runner->next = 0;
}