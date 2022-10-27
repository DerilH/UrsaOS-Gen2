#include "PageFrameAllocator.h"

uint64_t PageFrameAllocator::_memorySize = 0;
uint64_t PageFrameAllocator::_freeMemorySize = 0;
uint64_t PageFrameAllocator::_reservedMemorySize = 0;
bool PageFrameAllocator::_initialized = false;
Bitmap PageFrameAllocator::_bitmap;

void PageFrameAllocator::Init(MemoryMapEntry* mMap, uint8_t mMapEntriesCount, void* bitmapBuffer, uint32_t bitmapSize) 
{
	MemoryMapEntry entry;

	for(int i = 0; i < mMapEntriesCount; i++) 
	{
		entry = mMap[i]
	}
}