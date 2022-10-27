#include "Pit.h"
#include "../Devices/Screen.h"

double PIT::_timeSinceBoot = 0;
uint16_t PIT::_divisor = 65535;
Timer* PIT::_timers[32];

void PIT::Sleepd(double seconds) {
    double startTime = _timeSinceBoot;
    while (_timeSinceBoot < startTime + seconds) {
        asm("hlt");
    }
}
void PIT::Sleep(uint64_t milliseconds) {
    Sleepd((double)milliseconds / 1000);
}
void PIT::SetDivisor(uint16_t divisor) {
    if (divisor < 100) divisor = 100;
    _divisor = divisor;
    outb(0x40, (uint8_t)(divisor & 0x00ff));
    io_wait();
    outb(0x40, (uint8_t)((divisor & 0xff00) >> 8));
}
uint64_t PIT::GetFrequency() {
    return _baseFrequency / _divisor;
}
void PIT::SetFrequency(uint64_t frequency) {
    SetDivisor(_baseFrequency / frequency);
}
void PIT::Tick() {
    _timeSinceBoot += 1 / (double)GetFrequency();
    _callTimers(_timeSinceBoot);
}

void PIT::_setTimer(Timer* timer) 
{
    if (timer == nullptr) return;
    for (int i = 0; i < 32; i++) 
    {
        if (_timers[i] != nullptr) continue;
        _timers[i] = timer;
        break;
    }
}

void PIT::_removeTimer(Timer* timer)
{
    if (timer == nullptr) return;
    for (int i = 0; i < 32; i++)
    {
        if (_timers[i] != timer) continue;
        _timers[i] == nullptr;
        break;
    }
}

void PIT::_callTimers(uint64_t time) 
{
    for (int i = 0; i < 32; i++) 
    {
        if (_timers[i] == nullptr) continue;
        if (_timers[i]->_stopped) continue;
        if (time >= _timers[i]->_startTime + (_timers[i]->_interval / 1000))
        {
            _timers[i]->_call();
        }
    }
}

Timer::Timer(uint64_t intervalms)
{
    this->_interval = intervalms;
    PIT::_setTimer(this);
}

void Timer::SetInterval(uint64_t intervalms)
{
    this->_interval = intervalms;
};
void Timer::SetCallback(void (*callback)())
{
    this->_callback = callback;
};
void Timer::RemoveCallback()
{
    this->_callback = nullptr;
};
void Timer::Stop()
{
    this->_stopped = true;
};
void Timer::Start()
{
    this->_stopped = false;
    this->_startTime = PIT::_timeSinceBoot;
};

void Timer::_call() 
{
    if (_callback == nullptr) return;
    _callback();
    if (Cycled) 
    {
        Start();
    }
    else 
    {
        _stopped = true;
    }
}