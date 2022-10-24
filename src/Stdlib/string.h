#pragma once
#include <stdint.h>
const char *to_string(float num, int precision);

const char* to_string(uint8_t num);
const char* to_string(uint16_t num);
const char* to_string(uint32_t num);
const char* to_string(uint64_t num);
const char* to_string(int8_t num);
const char* to_string(int16_t num);
const char* to_string(int32_t num);
const char* to_string(int64_t num);

const char *hextos(uint8_t value);
const char *hextos(uint16_t value);
const char *hextos(uint32_t value);
const char *hextos(uint64_t value);

bool cmpStrs(char string1[], const char* string2);