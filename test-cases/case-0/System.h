#pragma once
#include "ExternalData.h"

class System
{
        public:
    struct Data
    {
        double x;
        double y;
        int z;
        bool isValid;
        foo::ExtData extData;
    };

    void registerData();

        private:
    /// \register data
    Data mData = {0};
    /// \register output
    Data mOut;
};