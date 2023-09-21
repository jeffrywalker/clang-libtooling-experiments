#include "SubSystem.h"
#include <iostream>
#include <typeinfo>

SubSystem::SubSystem()
{
    posNed.x(100.0);
}

SubSystem::SubData* SubSystem::_data()
{
    return &mData;
}

foo::States* SubSystem::_states()
{
    return static_cast<foo::States*>(this);
}