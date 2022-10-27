#pragma once 
#include <stdint.h>
#include "../Interrupts/IO.h"
#include "../Stdlib/string.h"

struct DateTime
{
    uint8_t second;
    uint8_t minute;
    uint8_t hour;
    uint8_t day;
    uint8_t month;
    uint32_t year;
};

class RTC 
{
private:
    static uint8_t _second;
    static uint8_t _minute;
    static uint8_t _hour;
    static uint8_t _day;
    static uint8_t _month;
    static uint32_t _year;
    static uint32_t _century;

public:
    static void Update();
    static uint8_t GetSecond();
    static uint8_t GetMinute();
    static uint8_t GetHour();
    static uint8_t GetDay();
    static uint8_t GetMonth();
    static uint32_t GetYear();

    static const char* GetFullDateAsString();
    static DateTime GetDate();
};