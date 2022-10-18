#pragma once
#include <stdint.h>
#include "Print.h"
#include "IO.h"
#include "string.h"
#include "KBScanCodeSet1.h"
#include "KeyboardHandler.h"

struct IDT
{
    uint16_t offset_low;
    uint16_t selector;
    uint8_t ist;
    uint8_t types_attr;
    uint16_t offset_mid;
    uint32_t offset_high;
    uint32_t re_zero;
};

void InitializeIDT();
