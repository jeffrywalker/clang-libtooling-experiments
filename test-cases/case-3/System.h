#pragma once
#include "SubSystem.h"
#include "Vector3.h"

class System
{
        public:
    struct Data
    {
        double a;
        double b;
        int c;
        bool isValid;
        Vector3 position;
    };

    void registerData();

        private:
    SubSystem mSubSystem;
    Data mData = {0};
};