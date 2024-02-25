#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main(void)
{
    cout << "Bool: " << true << "," << false <<
        "; string format: " << boolalpha << true << "," << false << "\n";
    cout << "Decimal: " << 16 << ", octal: " << oct << 16 << ", hex: " << hex << 16 << "\n" << dec;
    cout << "General: " << 1.2345 << ", scientific: " << scientific << 1.2345 << "\n";
    cout << "Precision(2): " << fixed << setprecision(2) << 1.2345 << endl;
}
