#include "Time.h"
#define CURRENT_YEAR 2022

enum
{
    cmos_address = 0x70,
    cmos_data = 0x71
};

int century_register = 0;

int get_update_in_progress_flag() {
    outb(cmos_address, 0x0A);
    return (inb(cmos_data) & 0x80);
}

unsigned char get_RTC_register(int reg) {
    outb(cmos_address, reg);
    return inb(cmos_data);
}

uint8_t RTC::_second = 0;
uint8_t RTC::_minute = 0;
uint8_t RTC::_hour = 0;
uint8_t RTC::_day = 0;
uint8_t RTC::_month = 0;
uint32_t RTC::_year = 0;
uint32_t RTC::_century = 0;

void RTC::Update()
{
    unsigned char century;
    unsigned char last_second;
    unsigned char last_minute;
    unsigned char last_hour;
    unsigned char last_day;
    unsigned char last_month;
    unsigned char last_year;
    unsigned char last_century;
    unsigned char registerB;

    // Note: This uses the "read registers until you get the same values twice in a row" technique
    //       to avoid getting dodgy/inconsistent values due to RTC updates

    while (get_update_in_progress_flag());                // Make sure an update isn't in progress
    _second = get_RTC_register(0x00);
    _minute = get_RTC_register(0x02);
    _hour = get_RTC_register(0x04);
    _day = get_RTC_register(0x07);
    _month = get_RTC_register(0x08);
    _year = get_RTC_register(0x09);
    if (century_register != 0) {
        _century = get_RTC_register(century_register);
    }

    do {
        last_second = _second;
        last_minute = _minute;
        last_hour = _hour;
        last_day = _day;
        last_month = _month;
        last_year = _year;
        last_century = _century;

        while (get_update_in_progress_flag());           // Make sure an update isn't in progress
        _second = get_RTC_register(0x00);
        _minute = get_RTC_register(0x02);
        _hour = get_RTC_register(0x04);
        _day = get_RTC_register(0x07);
        _month = get_RTC_register(0x08);
        _year = get_RTC_register(0x09);
        if (century_register != 0) {
            _century = get_RTC_register(century_register);
        }
    } while ((last_second != _second) || (last_minute != _minute) || (last_hour != _hour) ||
        (last_day != _day) || (last_month != _month) || (last_year != _year) ||
        (last_century != _century));

    registerB = get_RTC_register(0x0B);

    // Convert BCD to binary values if necessary

    if (!(registerB & 0x04)) {
        _second = (_second & 0x0F) + ((_second / 16) * 10);
        _minute = (_minute & 0x0F) + ((_minute / 16) * 10);
        _hour = ((_hour & 0x0F) + (((_hour & 0x70) / 16) * 10)) | (_hour & 0x80);
        _day = (_day & 0x0F) + ((_day / 16) * 10);
        _month = (_month & 0x0F) + ((_month / 16) * 10);
        _year = (_year & 0x0F) + ((_year / 16) * 10);
        if (century_register != 0) {
            _century = (_century & 0x0F) + ((_century / 16) * 10);
        }
    }

    // Convert 12 hour clock to 24 hour clock if necessary

    if (!(registerB & 0x02) && (_hour & 0x80)) {
        _hour = ((_hour & 0x7F) + 12) % 24;
    }

    // Calculate the full (4-digit) year

    if (century_register != 0) {
        _year += _century * 100;
    }
    else {
        _year += (CURRENT_YEAR / 100) * 100;
        if (_year < CURRENT_YEAR) _year += 100;
    }
}
uint8_t RTC::GetSecond() {return _second;}
uint8_t RTC::GetMinute() {return _minute;}
uint8_t RTC::GetHour()   {return _hour;}
uint8_t RTC::GetDay()    {return _day;}
uint8_t RTC::GetMonth()  {return _month;}
uint32_t RTC::GetYear()   {return _year;}


char dateBuffer[20];
const char* RTC::GetFullDateAsString()
{


    Update();
    const char* temp = to_string(_second);
    if (_second < 10) 
    {
        dateBuffer[1] = temp[0];
        dateBuffer[0] = temp[1];

    }
    else 
    {
        dateBuffer[0] = temp[0];
        dateBuffer[1] = temp[1];
    }
    dateBuffer[2] = ':';
    temp = to_string(_minute);
    if (_minute < 10)
    {
        dateBuffer[4] = temp[0];
        dateBuffer[3] = temp[1];

    }
    else
    {
        dateBuffer[3] = temp[0];
        dateBuffer[4] = temp[1];
    }
    dateBuffer[5] = ':';
    temp = to_string(_hour);

    if (_hour < 10)
    {
        dateBuffer[7] = temp[0];
        dateBuffer[6] = temp[1];

    }
    else
    {
        dateBuffer[6] = temp[0];
        dateBuffer[7] = temp[1];
    }
    dateBuffer[8] = ' ';
    temp = to_string(_day);

    if (_day < 10)
    {
        dateBuffer[10] = temp[0];
        dateBuffer[9] = temp[1];

    }
    else
    {
        dateBuffer[9] = temp[0];
        dateBuffer[10] = temp[1];
    }
    dateBuffer[11] = '-';
    temp = to_string(_month);
    dateBuffer[12] = temp[0];
    dateBuffer[13] = temp[1];
    dateBuffer[14] = '-';
    if (_month < 10)
    {
        dateBuffer[16] = temp[0];
        dateBuffer[15] = temp[1];

    }
    else
    {
        dateBuffer[15] = temp[0];
        dateBuffer[16] = temp[1];
    }
    temp = to_string(_year);
    dateBuffer[15] = temp[0];
    dateBuffer[16] = temp[1];
    dateBuffer[17] = temp[2];
    dateBuffer[18] = temp[3];
    
    for (int i = 0; i < 19; i++)
    {
        if (dateBuffer[i] == 0) 
        {
            dateBuffer[i] = '0';
        }

    }

    dateBuffer[19] = 0;
    return dateBuffer;
}

DateTime RTC::GetDate()
{
    Update();
    DateTime dt;
    dt.second = _second;
    dt.minute = _minute;
    dt.hour = _hour;
    dt.day = _day;
    dt.month = _month;
    dt.year = _year;
    return dt;
}



