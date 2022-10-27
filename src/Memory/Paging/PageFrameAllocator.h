#pragma once
#include <stdint.h>
#include "../../Stdlib/Bitmap.h"
#include "../Memory.h"
#include "../MemoryMap.h"

class PageFrameAllocator 
{
private:
	static uint64_t _memorySize;
	static uint64_t _freeMemorySize;
	static uint64_t _reservedMemorySize;
	static bool _initialized;
	static Bitmap _bitmap;

	PageFrameAllocator();
public:
	static void Init(MemoryMapEntry* mMap, uint8_t mMapEntriesCount, void* bitmapBuffer, uint32_t bitmapSize);
	static void FreePage();
	static void LockPage();
	static void RequestPage();
};