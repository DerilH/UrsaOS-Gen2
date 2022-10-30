#include "Memory.h"
#define MINALLOC 8

MemorySegmentHeader *heapStart;
MemorySegmentHeader *FirstFreeMemorySegment;

void MergeSegments(MemorySegmentHeader* firstSeg, MemorySegmentHeader* secondSeg);

void InitHeap(uint64_t address, uint64_t size)
{
    heapStart = (MemorySegmentHeader *)address;
    FirstFreeMemorySegment = heapStart;
    heapStart->lenght = size - sizeof(MemorySegmentHeader);
    heapStart->nextFreeSeg = 0;
    heapStart->prevFreeSeg = 0;
    heapStart->nextSeg = 0;
    heapStart->nextSeg = 0;
    heapStart->Free = true;
}
void *kmalloc(uint64_t size)
{
    if (size < MINALLOC)
    {
        size += MINALLOC;
    }

    MemorySegmentHeader *currentSeg = heapStart;
    while (true)
    {
        if (currentSeg->Free && currentSeg->lenght >= size)
        {

            MemorySegmentHeader *newMemSeg;

            if (currentSeg->lenght == size)
            {
                currentSeg->Free = false;
                newMemSeg = currentSeg;
                return newMemSeg + 1;
            }

            newMemSeg = (MemorySegmentHeader *)(((uint64_t)currentSeg) + sizeof(MemorySegmentHeader) + size);
            newMemSeg->prevSeg = currentSeg;
            newMemSeg->lenght = currentSeg->lenght - size - sizeof(MemorySegmentHeader);
            newMemSeg->Free = true;

            currentSeg->nextSeg = newMemSeg;
            currentSeg->lenght = size;
            currentSeg->Free = false;
            return currentSeg + 1;
        }
        if (currentSeg->nextSeg != 0)
        {
            currentSeg = currentSeg->nextSeg;
        }
        else
            return 0;
    }
}

void kfree(void *ptr)
{
    MemorySegmentHeader *segment = (MemorySegmentHeader *)((uint64_t)ptr - sizeof(MemorySegmentHeader));
    segment->Free = true;
    if(segment->nextSeg->Free == true) 
    {
        MergeSegments(segment, segment->nextSeg);
    }
    else if(segment->prevSeg->Free == true) 
    {
        MergeSegments(segment->prevSeg, segment);
    }
}

void* memset(void* start, uint8_t value, uint64_t num) {
    for (uint64_t i = 0; i < num; i++) {
        *(uint8_t*)((uint64_t)start + i) = value;
    }
    return start;
}

void *memcpy(void *dst, const void *src, uint64_t n)
{
    int i, m;
    unsigned long *wdst = (unsigned long*)dst; // текущая позиция в буфере назначения
    unsigned long *wsrc = (unsigned long*)src; // текущая позиция в источнике
    unsigned char *cdst, *csrc;

    for (i = 0, m = n / sizeof(long); i < m; i++) // копируем основную часть блоками по 4 или 8 байт
        *(wdst++) = *(wsrc++);                    // (в зависимости от платформы)

    cdst = (unsigned char *)wdst;
    csrc = (unsigned char *)wsrc;

    for (i = 0, m = n % sizeof(long); i < m; i++) // остаток копируем побайтно
        *(cdst++) = *(csrc++);

    return dst;
}

void* kcalloc(uint64_t num, uint64_t size) 
{
    void* mallVal = kmalloc(num * size);
    if(mallVal == 0) return 0;
    return mallVal;
}

void MergeSegments(MemorySegmentHeader* firstSeg, MemorySegmentHeader* secondSeg) 
{
    firstSeg->Free == true;
    firstSeg->lenght += secondSeg->lenght + sizeof(MemorySegmentHeader);
    firstSeg->nextSeg = secondSeg->nextSeg;
    firstSeg->nextSeg->prevSeg = firstSeg;
}