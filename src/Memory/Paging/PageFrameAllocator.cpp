#include "PageFrameAllocator.h"

uint64_t PageFrameAllocator::_memorySize = 0;
uint64_t PageFrameAllocator::_freeMemorySize = 0;
uint64_t PageFrameAllocator::_usedMemorySize = 0;
uint64_t PageFrameAllocator::_reservedMemorySize = 0;
bool PageFrameAllocator::_initialized = false;
Bitmap PageFrameAllocator::_bitmap;
MemoryMapEntry* PageFrameAllocator::_mMap = nullptr;
uint16_t PageFrameAllocator::_mMapEntriesCount = 0;
MemoryMapEntry* PageFrameAllocator::_largestFreeMemSeg = nullptr;

void PageFrameAllocator::_readMemoryMap() 
{
	MemoryMapEntry* entry;
	_largestFreeMemSeg = _mMap;
	int i = 0;
	for (; i < _mMapEntriesCount; i++)
	{
		entry = _mMap;
		_memorySize += entry->size;
		
		switch (entry->type)
		{
		case USABLE_MEMREG:
			_freeMemorySize += entry->size;
			break;
		default:
			_reservedMemorySize += entry->size;
			break;
		}

		if (entry->size > _largestFreeMemSeg->size)
			_largestFreeMemSeg = entry;

		_mMap++;
	}

	_mMap -= i;
}

void PageFrameAllocator::Init(MemoryMapEntry* mMap, uint8_t mMapEntriesCount) 
{
	_mMap = mMap;
	_mMapEntriesCount = mMapEntriesCount;

	_readMemoryMap();

	int bitmapSize = _memorySize / 4096 / 8 + 1;
	_bitmap = Bitmap(bitmapSize, (uint8_t*)_largestFreeMemSeg->address);
    _bitmap.Clear();

    PageFrameAllocator::LockPages(&_bitmap, bitmapSize / 4096 + 1);

	MemoryMapEntry* entry;
	int i = 0;
	for (; i < _mMapEntriesCount; i++)
	{
		entry = _mMap;
		
		if(entry->type == RESERVED_MEMREG || entry->type == ACPI_NVS_MEMREG || entry->type == ACPI_RECLAIMED_MEMREG || entry->type == BAD_MEMREG)
			ReservePages((void*)entry->address, entry->size / 4096 + 1);

		_mMap++;
	}

	_mMap -= i;
}

uint64_t PageFrameAllocator::GetFullMemorySize()
{
	return _memorySize;
}
uint64_t PageFrameAllocator::GetReservedMemorySize()
{
	return _reservedMemorySize;
}
uint64_t PageFrameAllocator::GetFreeMemorySize() 
{
	return _freeMemorySize;
}

uint64_t PageFrameAllocator::GetUsedMemorySize()
{
	return _usedMemorySize;
}

void* PageFrameAllocator::RequestPage() {
    for (uint64_t index = 0; index < _bitmap.Size * 8; index++) {
        if (_bitmap[index] == true) continue;
        LockPage((void*)(index * 4096));
        return (void*)(index * 4096);
    }

    return nullptr; // Page Frame Swap to file
}

void PageFrameAllocator::FreePage(void* address) {
    uint64_t index = (uint64_t)address / 4096;
    if (_bitmap[index] == false) return;
    _bitmap.Set(index, false);
    _freeMemorySize += 4096;
    _usedMemorySize -= 4096;
}

void PageFrameAllocator::FreePages(void* address, uint64_t pageCount) {
    for (int t = 0; t < pageCount; t++) {
        FreePage((void*)((uint64_t)address + (t * 4096)));
    }
}

void PageFrameAllocator::LockPage(void* address) {
    uint64_t index = (uint64_t)address / 4096;
    if (_bitmap[index] == true) return;
    _bitmap.Set(index, true);
    _freeMemorySize -= 4096;
    _usedMemorySize += 4096;
}

void PageFrameAllocator::LockPages(void* address, uint64_t pageCount) {
    for (int t = 0; t < pageCount; t++) {
        LockPage((void*)((uint64_t)address + (t * 4096)));
    }
}

void PageFrameAllocator::UnreservePage(void* address) {
    uint64_t index = (uint64_t)address / 4096;
    if (_bitmap[index] == false) return;
    _bitmap.Set(index, false);
    _freeMemorySize += 4096;
    _reservedMemorySize -= 4096;
}

void PageFrameAllocator::UnreservePages(void* address, uint64_t pageCount) {
    for (int t = 0; t < pageCount; t++) {
        UnreservePage((void*)((uint64_t)address + (t * 4096)));
    }
}

void PageFrameAllocator::ReservePage(void* address) {
    uint64_t index = (uint64_t)address / 4096;
    if (_bitmap[index] == true) return;
    _bitmap.Set(index, true);
    _freeMemorySize -= 4096;
    _reservedMemorySize += 4096;
}

void PageFrameAllocator::ReservePages(void* address, uint64_t pageCount) {
    for (int t = 0; t < pageCount; t++) {
        ReservePage((void*)((uint64_t)address + (t * 4096)));
    }
}

void PageFrameAllocator::PrintBitmap() 
{
	for (int i = 0; i < _bitmap.Size ;i++) 
	{
		Shell::CurrentShell->Print(to_string(_bitmap[i]));
	}
}
