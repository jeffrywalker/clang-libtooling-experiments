#pragma once
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
    Data mData = {0};
};