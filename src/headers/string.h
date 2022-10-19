#pragma once
#include <stdint.h>

const char *to_string(int num);
const char *to_string(float num, int precision);

const char *hextos(uint8_t value);
const char *hextos(uint16_t value);
const char *hextos(uint32_t value);
const char *hextos(uint64_t value);

bool cmpStrs(char string1[], const char* string2);