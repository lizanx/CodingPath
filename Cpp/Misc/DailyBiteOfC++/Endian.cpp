#include <bit>
#include <print>

int main()
{
    if constexpr (std::endian::native == std::endian::little)
    {
        std::println("This system is Little-Endian");
    }
    else if constexpr (std::endian::native == std::endian::big)
    {
        std::println("This system is Big-Endian");
    }
}
