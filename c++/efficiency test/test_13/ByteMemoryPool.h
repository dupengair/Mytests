#ifndef BYTEMEMORYPOOL_H
#define BYTEMEMORYPOL_H

#include <stdlib.h>
#include "MemoryChunk.h"

class ByteMemoryPool {
public:
    ByteMemoryPool (size_t initSize = MemoryChunk::DEFAULT_CHUNK_SIZE);
    ~ByteMemoryPool();

    void *alloc (size_t size);
    void free (void* doomed);
        
private:
    MemoryChunk* listOfMemoryChunks;
    void expandStorage(size_t reqSize);
};

#endif
