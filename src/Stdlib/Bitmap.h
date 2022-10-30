#pragma once
#include <stdint.h>

class Bitmap {
    uint8_t* _buffer;
public:
    uint64_t Size;
    Bitmap();
    Bitmap(uint64_t size, uint8_t* buffer);
    bool operator[](uint64_t index);
    void Set(uint64_t index, bool value);
    void Clear();
};
