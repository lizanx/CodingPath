#include <iostream>

namespace
{
    // Of size 1byte
    class EmptyCls
    {
    };
}

int main(int argc, char *argv[])
{
    EmptyCls obj1{};
    EmptyCls obj2{};
    EmptyCls obj3{};

    std::cout << "Size of EmptyCls: " << sizeof(EmptyCls) << "\n"
              << "Addr of obj1: " << &obj1 << "\n"
              << "Addr of obj2: " << &obj2 << "\n"
              << "Addr of obj3: " << &obj3 << "\n";
}
