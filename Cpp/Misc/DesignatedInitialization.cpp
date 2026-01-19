#include <iostream>

using namespace std;

namespace
{
    struct Data
    {
        int A{};
        int B;
        int C{1};
        int D{2};
    };

    std::ostream &operator<<(std::ostream &os, const Data &d)
    {
        os << "Data{ A = " << d.A
           << ", B = " << d.B
           << ", C = " << d.C
           << ", D = " << d.D
           << " }";
        return os;
    }
}

int main()
{
    Data d1 = {
        .A = 1,
        .B = 2,
    };
    Data d2 = {
        .B = 3, // !!!warning/error: should follow member initialization order.
        .A = 5,
    };
    Data d3 = {
        .D = 9,
    };
    cout << "d1: " << d1 << "\n"
         << "d2: " << d2 << "\n"
         << "d3: " << d3 << "\n";

    return 0;
}
