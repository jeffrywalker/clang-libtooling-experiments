
struct ChildInp
{
    /// child x
    double x;
    /// child y
    double y;
};
struct ChildOut
{
    /// child y
    double y;
};
struct ChildStates
{
    /// \units s
    double time;
};

class Child
{
        public:
    ChildInp m_inp;
    ChildOut m_out;
    ChildStates m_x;
};