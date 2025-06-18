#include <cstring>
#include <iostream>

namespace
{
    int violation(float *f, int *i)
    {
        *i = 1;
        *f = 0.f;

        // With higher optimization level(-O2 in this case),
        // the compiler may assume that "f" won't impact value of "i",
        // since "float*" and "int*" are not valid similar types.
        // Then it may optimize away "loading value from address i",
        // and directly return "1" which is already stored in register.
        return *i;
    }

    int no_violation(float *f, int *i)
    {
        static_assert(sizeof(float) == sizeof(int), "Size of int/float not equal!");
        *f = 0;

        std::memcpy(i, f, sizeof(int));

        return *i;
    }

    void alignment()
    {
        static_assert(sizeof(int) == sizeof(char) * 4, "Size of int not 4 times of char!");

        alignas(alignof(int)) char arr[5] = {0};
        auto x = reinterpret_cast<int *>(arr); // OK, arr is aligned with 4B
        *x = 0xffffff;                         // 16777215
        std::cout << "x = " << *x << "\n";

        // !!! Undefined behavior, enough size, but not aligned
        // It may execute normally, but on other architectures/with other compilers it may crash!
        auto y = reinterpret_cast<int *>(arr + 1);
        std::cout << "y = " << *y << "\n";

        auto z = new (arr) int{0}; // OK
        std::cout << "z = " << *z << "\n";
    }
}

int main()
{
    int x = 0;

    std::cout << x << "\n"; // Expect 0
    x = violation(reinterpret_cast<float *>(&x), &x);
    std::cout << x << "\n"; // !!! Try with "-O0" and "-O2"

    std::cout << "-----------------------------------\n";

    x = 0;
    std::cout << x << "\n"; // Expect 0
    x = no_violation(reinterpret_cast<float *>(&x), &x);
    std::cout << x << "\n"; // !!! Try with "-O0" and "-O2"

    std::cout << "-----------------------------------\n";
    alignment();
}
