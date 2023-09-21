#pragma once
#include "Eom.h"

class System
{
        public:
    void step();
    void registerData();

    eom::Eom& getEom();

        private:
    eom::Eom mEom;
};