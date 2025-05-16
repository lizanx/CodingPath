// *****************************************************************************
// include
// *****************************************************************************
// library header files
#include "tinylib.hpp"   // library header file

// project component header files
#include "x.hpp"
#include "y.hpp"

// *****************************************************************************
// main
// *****************************************************************************
int main(int argc, char* args[])
{
    cout << "Testing tinyproj" << endl;
    cout << "Project component x: ";
    x_print();

    cout << "Project component y: ";
    y_print();

    cout << "Using tinylib library component a1: ";
    a1_print();

    cout << "Using tinylib library component b1: ";
    b1_print();

    return 0;
}   // main
