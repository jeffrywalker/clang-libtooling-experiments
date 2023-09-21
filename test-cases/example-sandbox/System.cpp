#include "System.h"

void System::step()
{
    mEom.step();
}

eom::Eom& System::getEom()
{
    return mEom;
}

void System::registerData()
{
    // objective, register the eom states which are private
}