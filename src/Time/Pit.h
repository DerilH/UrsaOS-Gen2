#pragma once

#include <stdint.h>

extern volatile uint32_t g_pitTicks;

void PitInit();
void PitWait(unsigned int ms);