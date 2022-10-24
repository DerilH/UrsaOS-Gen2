#include "Constructors.h"

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;

bool called = false;

extern "C" void callConstructors()
{
    if(called) return;
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
     (*i)();

    called = true;
}