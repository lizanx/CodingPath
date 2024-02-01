#include <iostream>
#include <limits>

int main(int argc, char *argv[])
{
    using std::numeric_limits, std::cout, std::endl;

    cout << "int: min = " << numeric_limits<int>::min() <<
        ", max = " << numeric_limits<int>::max() <<
        ", signed = " << numeric_limits<int>::is_signed <<
        ", is_integer = " << numeric_limits<int>::is_integer << endl;

    cout << "double: min = " << numeric_limits<double>::min() <<
        ", max = " << numeric_limits<double>::max() <<
        ", signed = " << numeric_limits<double>::is_signed <<
        ", is_integer = " << numeric_limits<double>::is_integer << endl;
}