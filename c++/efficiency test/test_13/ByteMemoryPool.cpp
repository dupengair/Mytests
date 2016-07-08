#include "ByteMemoryPool.h"

ByteMemoryPool::ByteMemoryPool(size_t initSize)
{
    expandStorage(initSize);
}

ByteMemoryPool::~ByteMemoryPool()
{
    MemoryChunk *memChunk = listOfMemoryChunks;

    while(memChunk) {
        listOfMemoryChunks = memChunk->nextMemChunk();
        delete memChunk;
        memChunk = listOfMemoryChunks;
        }
}

void* ByteMemoryPool::alloc(size_t requestSize)
{
    size_t space = listOfMemoryChunks->spaceAvailable();
    if(space < requestSize) {
        expandStorage(requestSize);
        }

    return listOfMemoryChunks->alloc(requestSize);
}

void ByteMemoryPool::free(void *doomed)
{
    listOfMemoryChunks->free(doomed);
}

void ByteMemoryPool::expandStorage(size_t reqSize)
{
    listOfMemoryChunks = new MemoryChunk(listOfMemoryChunks, reqSize);
}