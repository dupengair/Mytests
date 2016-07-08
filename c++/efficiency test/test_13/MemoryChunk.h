#ifndef MEMORYCHUNK_H
#define MEMORYCHUNK_H

#include <stdlib.h>

class MemoryChunk {
public:
    MemoryChunk (MemoryChunk *nextChunk, size_t reqSize);
    ~MemoryChunk() { delete [] mem; }

    void *alloc (size_t size);
    inline void free (void* doomed) {}

    MemoryChunk *nextMemChunk() { return next; }
    size_t spaceAvailable() { return chunkSize - bytesAlreadyAllocated; }

    enum { DEFAULT_CHUNK_SIZE = 4096 };

private:
    MemoryChunk *next;
    void *mem;

    size_t chunkSize;
    size_t bytesAlreadyAllocated;

};


#endif
