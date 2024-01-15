/// template base data class
template <class Inputs, class Outputs, class Internals> class DataBase : public Inputs, public Outputs, public Internals
{
};

namespace ns_ShipData
{
    struct INP
    {
        double u;
    };

    struct OUT
    {
        double x;
    };

    struct DataNode
    {
        int foo;
        double baz;
    };

    struct INT
    {
        int count;
        DataNode leftNode;
        DataNode rightNode;
    };

    typedef DataBase<INP, OUT, INT> DataModel;

}  // namespace ns_ShipData

namespace ns_AircraftData
{
    struct Inputs
    {
        double u;
    };

    struct Outputs
    {
        double x;
    };

    struct Internals
    {
        int count;
    };

    typedef DataBase<Inputs, Outputs, Internals> Model;

}  // namespace ns_AircraftData

class Ship : public ns_ShipData::DataModel
{
        public:
    void registerData();
    /// \units kts
    double cruiseSpeed;
    /// \units deg
    /// \convention [0, 360]
    double heading;
};
class Aircraft : public ns_AircraftData::Model
{
    void registerData();
};

class Vehicles
{
    void registerData();
    void registerShip(Ship& ship);
    void registerAv(Aircraft& av);

    Ship ship;
    Aircraft aircraft;
};