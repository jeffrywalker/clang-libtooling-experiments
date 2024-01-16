enum class Mode
{
    OFF = 0,
    ON,
    IDLE
};

struct Fruit
{
    int apple[2];
    unsigned long orange;
};

struct Vec3
{
    /// \units inherit
    double x;
    /// \units inherit
    double y[3];
    /// \units inherit
    double z;
    Fruit fruits[3];
};

struct Inputs
{
    /// primary input
    /// \units ft
    double u;
    /// operational mode
    // Mode mode_a;
    /// operational mode
    // Mode mode_b;
    Vec3 pass;

    /// array input
    // double ainp[3][2];
    // Mode foo[2];
    Vec3 structArray[2][3];

    /// std array
    // std::array<int, 5> foo;
};

// struct Vehicle
// {
//     /// the power of foo
//     int foo;
//     /// \units ft/s
//     Vec3 velocity;
//     /// \units rad/s
//     Vec3 angularVelocity;
// };
// struct Fruit
// {
//     int apple;
//     int orange;
// };
//
// struct AirVehicle : public Vehicle, private Fruit
// {
//     /// \units kts
//     double airspeed;
//     /// \units m
//     double altitude;
// };
//
struct Outputs
{
    /// y output
    double y;
    /// \units ft
    // Vec3 position;
    // /// my vehicle
    // Vehicle myVehicle;
    // /// aircraft
    // AirVehicle airVehicle;
};

class MyClass
{
        public:
    // void step(Outputs& out, const Inputs& inp);

    bool registerData(const std::wstring& listName, IVarData* pVarData);

    /// system input data
    Inputs m_inp;
    /// system output data
    Outputs m_out;
};