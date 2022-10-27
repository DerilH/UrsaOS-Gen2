#pragma once
#include <stdint.h>
#include "../Interrupts/IO.h"

class Timer;
class PIT 
{
    friend class Timer;
private:
    static const uint64_t _baseFrequency = 1193182;
    static double _timeSinceBoot;
    static uint16_t _divisor;
        
    static Timer* _timers[32];
    static void _setTimer(Timer* timer);
    static void _removeTimer(Timer* timer);
    static void _callTimers(uint64_t time);
public:
    static void Sleepd(double seconds);
    static void Sleep(uint64_t milliseconds);
    static void SetDivisor(uint16_t divisor);
    static uint64_t GetFrequency();
    static void SetFrequency(uint64_t frequency);
    static void Tick();
};

class Timer
{
    friend class PIT;
private:
    bool _stopped = true;
    uint64_t _interval = 0;
    double _startTime = 0;
    void (*_callback)() = nullptr;
    void _call();
public:
    bool Cycled = false;
    Timer(uint64_t intervalms);
    void SetInterval(uint64_t intervalms);
    void SetCallback(void (*callback)());
    void RemoveCallback();
    void Stop();
    void Start();
};