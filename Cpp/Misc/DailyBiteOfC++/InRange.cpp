#include <concepts>
#include <cstdint>
#include <utility>
#include <iostream>
#include <stdexcept>

namespace
{
    void SomeFunc(uint16_t value)
    {
        std::cout << "The 16bit value is " << value << '\n';
    }
}

void SomeWrapperFunc(std::integral auto value)
{
    if (!std::in_range<uint16_t>(value))
        throw std::out_of_range{"Value cannot be represented as uint16_t!"};
    SomeFunc(value);
}

int main()
{
    try
    {
        SomeWrapperFunc(-1);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Failed to call func with -1\n";
    }
    try
    {
        SomeWrapperFunc(99);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Failed to call func with 99\n";
    }
}
