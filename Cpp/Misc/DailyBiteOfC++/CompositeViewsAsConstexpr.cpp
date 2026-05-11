#include <cassert>
#include <ranges>
#include <string>

int main()
{
    constexpr auto trimFront = std::views::drop_while([](int c)
                                                      { return std::isspace(c); });
    constexpr auto trimBack = std::views::reverse | trimFront | std::views::reverse;
    constexpr auto trimSpace = trimBack | trimFront;

    std::string str = "   abc  \t  ";
    auto lazyTrimmed = str | trimSpace;
    std::string trimmedStr{lazyTrimmed.begin(), lazyTrimmed.end()};
    assert(trimmedStr == "abc");

    return 0;
}
