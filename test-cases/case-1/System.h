#pragma once
#include "ExternalData.h"

class System : public foo::Outputs, protected foo::Inputs, private foo::Data
{
        public:
    System();

    void registerData();

        protected:
    double someValue;

        private:
    void zeroData();
};