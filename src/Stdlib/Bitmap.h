#pragma once
#include <stddef.h>
#include <stdint.h>

class Bitmap {
public:
    uint64_t Size;
    uint8_t* Buffer;
    bool operator[](uint64_t index);
    void Set(uint64_t index, bool value);
};
