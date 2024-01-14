enum class Mode
{
    OFF = 0,
    ON,
    IDLE
};

struct Vec3
{
    /// \units inherit
    double x;
    /// \units inherit
    double y;
    /// \units inherit
    double z;
};

struct Inputs
{
    /// primary input
    /// \units ft
    double u;
    /// operational mode
    Mode mode;
};

struct Vehicle
{
    /// the power of foo
    int foo;
    /// \units ft/s
    Vec3 velocity;
    /// \units rad/s
    Vec3 angularVelocity;
};
struct Fruit
{
    int apple;
    int orange;
};

struct AirVehicle : public Vehicle, private Fruit
{
    /// \units kts
    double airspeed;
    /// \units m
    double altitude;
};

struct Outputs
{
    /// y output
    double y;
    /// \units ft
    Vec3 position;
    /// my vehicle
    Vehicle myVehicle;
    /// aircraft
    AirVehicle airVehicle;
};

class MyClass
{
        public:
    void step(Outputs& out, const Inputs& inp);

    void registerData();

    /// system input data
    Inputs m_inp;
    /// system output data
    Outputs m_out;
};