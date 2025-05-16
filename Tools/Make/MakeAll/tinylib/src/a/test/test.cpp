// *****************************************************************************
// include
// *****************************************************************************
// header file only (no object)
#include "always.hpp"

// object header files
#include "a.hpp"
#include "extra.hpp"

// *****************************************************************************
// main
// *****************************************************************************
int main(int argc, char* args[])
{
    cout << "Testing a (a1 + a2): " << endl;
    a1_print();
    a2_print();

    cout << "Testing extra: ";
    extra_print();

    return 0;
}   // main
