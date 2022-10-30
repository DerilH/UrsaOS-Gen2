#pragma once
#include <stdint.h>
#include "Paging.h"
#include "PageMapIndexer.h"
#include "PageFrameAllocator.h"
#include "../Memory.h"

class PageTableManager {
public:
    PageTableManager(PageTable* PML4Address);
    PageTable* PML4;
    void MapMemory(void* virtualMemory, void* physicalMemory);
};