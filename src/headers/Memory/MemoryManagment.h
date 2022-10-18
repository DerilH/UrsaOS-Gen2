#pragma once
#include <stdint.h>
#include "MemoryMap.h"

struct MemorySegmentHeader
{
    uint64_t lenght;
    MemorySegmentHeader* nextSeg;
    MemorySegmentHeader* prevSeg;
    MemorySegmentHeader* nextFreeSeg;
    MemorySegmentHeader* prevFreeSeg;
    bool Free = true;
};

void InitHeap(uint64_t address, uint64_t size);
void* malloc(uint64_t size);
void free(void *ptr);
void* memcpy(void* from, void* to, uint64_t amount);
void* calloc(uint64_t num, uint64_t size);
