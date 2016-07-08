
template <class POOLTYPE, class LOCK>
class MTMemoryPool {
public:
    void * alloc (size_t size);
    void free(void* someElement);

private:
    POOLTYPE stPool;
    LOCK theLock;
};

template <class M, class L>
void* MTMemoryPool<M, L>::alloc (size_t size)
{
    void* mem;
    theLock.Lock();
    mem = stPool.alloc(size);
    theLock.unLock();

    return mem;
}

template <class M, class L>
void MTMemoryPool<M, L>::free(void *doomed)
{
    theLock.Lock();
    stPool.free(doomed);
    theLock.unLock();
}
