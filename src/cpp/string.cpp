#include "../headers/string.h"

char itosBuffer[128];
char tempBuffer[128];
char floatstrBuffer[128];
char hexToStringOutput[128];

const char *to_string(int num)
{
  if(num == 0) return "0";
  uint8_t i = 0, x = 0;

  int div = 0;
  while (num != 0)
  {
    div = num % 10;
    num /= 10;
    tempBuffer[i] = div + 48;
    i++;
  }
  i--;
  while (i != 0)
  {
    itosBuffer[x] = tempBuffer[i];
    i--;
    x++;
  }
  itosBuffer[x] = tempBuffer[0];
  itosBuffer[x + 1] = 0;
  return itosBuffer;
}

const char *to_string(float num, int precision)
{
  int index = 0;
  to_string(num);
  while (itosBuffer[index] != 0)
  {
    floatstrBuffer[index] = itosBuffer[index];
    index++;
  };
  floatstrBuffer[index] = '.';
  index++;

  float decimalValue = num - (int)num;
  int i = 0;
  for (; i < precision; i++)
  {
    decimalValue *= 10;
    floatstrBuffer[index + i] = (int)decimalValue + 48;
    decimalValue -= (int)decimalValue;
  }
  floatstrBuffer[index + i + 1] = 0;
  return floatstrBuffer;
}

template <typename T>
const char *hextosT(T value)
{
  T *valPtr = &value;
  uint8_t *ptr;
  uint8_t temp;
  uint8_t size = (sizeof(T)) * 2 - 1;
  uint8_t i;
  for (i = 0; i < size; i++)
  {
    ptr = ((uint8_t *)valPtr + i);
    temp = ((*ptr & 0xF0) >> 4);
    hexToStringOutput[size - (i * 2 + 1)] = temp + (temp > 9 ? 55 : 48);
    temp = ((*ptr & 0x0F));
    hexToStringOutput[size - (i * 2 + 0)] = temp + (temp > 9 ? 55 : 48);
  }
  hexToStringOutput[size + 1] = 0;
  return hexToStringOutput;
}

const char *hextos(uint8_t value)  {return hextosT<uint8_t>(value);};
const char *hextos(uint16_t value) {return hextosT<uint16_t>(value);};
const char *hextos(uint32_t value) {return hextosT<uint32_t>(value);};
const char *hextos(uint64_t value) {return hextosT<uint64_t>(value);};

bool cmpStrs(char* string1, const char* string2)
{
  char* base = string1;
  int i = 0;
  while(string2[i] != 0) 
  {
    if(string1[i] != string2[i]) return false;
    i++;
  }
  return true;
} 