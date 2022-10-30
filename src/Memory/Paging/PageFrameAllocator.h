#pragma once
#include <stdint.h>
#include "../../Stdlib/Bitmap.h"
#include "../Memory.h"
#include "../MemoryMap.h"

struct MemoryMapEntry;

class PageFrameAllocator 
{
private:
	static uint64_t _memorySize;
	static uint64_t _freeMemorySize;
	static uint64_t _usedMemorySize;
	static uint64_t _reservedMemorySize;
	static bool _initialized;
	static Bitmap _bitmap;
	static MemoryMapEntry* _mMap;
	static uint16_t _mMapEntriesCount;
	static MemoryMapEntry* _largestFreeMemSeg;

	static void _readMemoryMap();
	PageFrameAllocator();
public:
	static void Init(MemoryMapEntry* mMap, uint8_t mMapEntriesCount);

	static uint64_t GetFullMemorySize();
	static uint64_t GetReservedMemorySize();
	static uint64_t GetFreeMemorySize();
	static uint64_t GetUsedMemorySize();

	static void* RequestPage();
	static void FreePage(void* address);
	static void FreePages(void* address, uint64_t pageCount);
	static void LockPage(void* address);
	static void LockPages(void* address, uint64_t pageCount);
	static void UnreservePage(void* address);
	static void UnreservePages(void* address, uint64_t pageCount);
	static void ReservePage(void* address);
	static void ReservePages(void* address, uint64_t pageCount);
	static void PrintBitmap();
};