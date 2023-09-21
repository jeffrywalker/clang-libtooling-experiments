#include "Eom.h"

using namespace eom;

Eom::States& Eom::getStates()
{
    return mX;
}

void Eom::step()
{
    mX.pos.x(mX.pos.x() + 1.0);
    mX.pos.y(mX.pos.y() + 2.0);
}