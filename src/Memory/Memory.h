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

void* memset(void* dst, uint8_t value, uint64_t num);
void InitHeap(uint64_t address, uint64_t size);
void* kmalloc(uint64_t size);
void kfree(void *ptr);
void* kmemcpy(void* from, void* to, uint64_t amount);
void* kcalloc(uint64_t num, uint64_t size);

//void* operator new(uint64_t size);
//void* operator new[](uint64_t size);
