#include <array>
#include <cstdio>
#include <stdexcept>

int main()
{
    constexpr auto terminationHandler = []()
    {
        printf("This is my custom termination handler.\n");
        fflush(stdout);
        std::abort();
    };

    std::set_terminate(terminationHandler);

    std::array<int, 4> arr{};
    for (std::size_t i{}; i < 5; ++i)
        arr.at(i) = i;

    return 0;
}
