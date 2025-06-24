#include <iostream>

namespace myname
{
    int var = 42; // According to GCC name decoration rules, this variable is named "_ZN6myname3varE" after compiling.
}

// Use command "g++ -S {filename}.cpp" to get "{filename.s}" and search inside it for "var",
// then you'll find the mangled name "_ZN6myname3varE".
extern "C" int _ZN6myname3varE;

int main(int argc, char *argv[])
{
    std::cout << "var = " << myname::var << "\n"
              << "_ZN6myname3varE = " << _ZN6myname3varE << "\n";

    return 0;
}
