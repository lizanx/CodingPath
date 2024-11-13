#include <bitset>
#include <iomanip>
#include <iostream>

int main()
{
    using namespace std;

    // Hex/Octal/Decimal
    cout << hex << 255 << "\n"
         << oct << 255 << "\n"
         << dec << 255 << "\n";

    // Bit set
    cout << "Bits of 255: " << bitset<sizeof(int)>{255} << "\n";

    // bool
    cout << true << " " << false << " -> "
         << boolalpha
         << true << " " << false << "\n";

    // Precision
    constexpr double PI = 3.14159;
    cout << PI << "\n"
         << setprecision(3) << PI << "\n"
         << scientific << PI << "\n"
         << fixed << PI << "\n";

    // Alignment
    cout << "##" << right << setw(10) << PI << "##" << "\n"
         << "##" << left << setw(8) << PI << "##" << "\n";

    return EXIT_SUCCESS;
}
