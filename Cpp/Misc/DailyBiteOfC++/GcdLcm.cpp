#include <numeric>
#include <cassert>

int main()
{
    assert((std::gcd(2 * 3, 3 * 5) == 3));
    assert(std::lcm(2 * 3, 3 * 5) == 2 * 3 * 5);

    return 0;
}
