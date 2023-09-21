#pragma once

namespace foo
{
    struct ExtData
    {
        double p;
        double q;
        double r;
    };

    struct Data
    {
        double x;
        double y;
        int z;
        bool isValid;
        ExtData extData;
    };

    struct Inputs
    {
        double a;
        double b;
        double c;
    };

    struct Outputs
    {
        double l;
        double m;
        double n;
    };
}  // namespace foo