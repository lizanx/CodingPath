#include <iterator>
#include <vector>
#include <list>
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"

template<typename T>
static typename T::value_type sum(const T& container)
{
    typename T::value_type result{};
    for (auto itr{container.cbegin()}; itr != container.cend(); itr++)
    {
        result += *itr;
    }
    return result;
}

TEST_CASE("Sum function")
{
    std::vector<int> vec{1, 2, 3};
    REQUIRE(sum(vec) == 6);

    std::list<int> lst{4, 5, 6};
    REQUIRE(sum(lst) == 15);
}