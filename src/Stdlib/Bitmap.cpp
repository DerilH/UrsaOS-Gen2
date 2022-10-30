#include "Bitmap.h"

Bitmap::Bitmap() {}

Bitmap::Bitmap(uint64_t size, uint8_t* buffer) 
{
    this->_buffer = buffer;
}

bool Bitmap::operator[](uint64_t index) {
    uint64_t byteIndex = index / 8;
    uint8_t bitIndex = index % 8;
    uint8_t bitIndexer = 0b10000000 >> bitIndex;
    if ((_buffer[byteIndex] & bitIndexer) > 0) {
        return true;
    }
    return false;
}

void Bitmap::Set(uint64_t index, bool value) {
    uint64_t byteIndex = index / 8;
    uint8_t bitIndex = index % 8;
    uint8_t bitIndexer = 0b10000000 >> bitIndex;
    _buffer[byteIndex] &= ~bitIndexer;
    if (value) {
        _buffer[byteIndex] |= bitIndexer;
    }
}

void Bitmap::Clear()
{
    for (int i = 0; i < Size; i++) {
        *(uint8_t*)(_buffer + i) = 0;
    }
}