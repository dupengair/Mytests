#include "MemoryChunk.h"

MemoryChunk::MemoryChunk(MemoryChunk *nextChunk, size_t reqSize)
{
    chunkSize = ( reqSize > DEFAULT_CHUNK_SIZE) ? reqSize : DEFAULT_CHUNK_SIZE;

    next = nextChunk;
    bytesAlreadyAllocated = 0;
    mem = new char [chunkSize];    
}

void* MemoryChunk::alloc(size_t requestSize)
{
    void *addr = reinterpret_cast<void*>(reinterpret_cast<size_t>(mem) + bytesAlreadyAllocated);
    bytesAlreadyAllocated += requestSize;

    return addr;
}

