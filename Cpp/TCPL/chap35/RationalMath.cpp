#include <iostream>
#include <ratio>

int main()
{
    using oneThird = std::ratio<1, 3>;
    using half = std::ratio<1, 2>;
    using oneSixth = std::ratio<1, 6>;

    using result = std::ratio_subtract<half, oneThird>;
    std::cout << half::num << "/" << half::den
              << " - "
              << oneThird::num << "/" << oneThird::den
              << " = "
              << result::num << "/" << result::den << "\n";
    std::cout << std::boolalpha << std::ratio_equal<result, oneSixth>::value << "\n";
}
