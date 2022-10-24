#pragma once 
#include <stdint.h>
#include "../Devices/Screen.h"

class Panic 
{
public:
	static void Invoke(const char* message);
};