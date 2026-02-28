#include <algorithm>
#include <cassert>
#include <vector>

int main()
{
    std::vector<int> emptyVec{};
    std::vector<int> vec{1, 2, 3, 4, 8, 9};

    auto isEven = [](int n)
    {
        return n % 2 == 0;
    };
    auto isOdd = [&isEven](int n)
    {
        return !isEven(n);
    };
    auto isSingleDigit = [](int n)
    {
        return n >= 0 && n <= 9;
    };

    // !!!! For empty sequence:
    // all_of -> true
    // none_of -> true
    // any_of -> false
    assert(std::all_of(emptyVec.begin(), emptyVec.end(), isEven) == true);
    assert(std::none_of(emptyVec.begin(), emptyVec.end(), isEven) == true);
    assert(std::any_of(emptyVec.begin(), emptyVec.end(), isEven) == false);
    assert(std::all_of(emptyVec.begin(), emptyVec.end(), isOdd) == true);
    assert(std::none_of(emptyVec.begin(), emptyVec.end(), isOdd) == true);
    assert(std::any_of(emptyVec.begin(), emptyVec.end(), isOdd) == false);
    assert(std::all_of(emptyVec.begin(), emptyVec.end(), isSingleDigit) == true);
    assert(std::none_of(emptyVec.begin(), emptyVec.end(), isSingleDigit) == true);
    assert(std::any_of(emptyVec.begin(), emptyVec.end(), isSingleDigit) == false);

    assert(std::all_of(vec.begin(), vec.end(), isEven) == false);
    assert(std::all_of(vec.begin(), vec.end(), isOdd) == false);
    assert(std::all_of(vec.begin(), vec.end(), isSingleDigit) == true);

    assert(std::none_of(vec.begin(), vec.end(), isEven) == false);
    assert(std::none_of(vec.begin(), vec.end(), isOdd) == false);
    assert(std::none_of(vec.begin(), vec.end(), isSingleDigit) == false);

    assert(std::any_of(vec.begin(), vec.end(), isEven) == true);
    assert(std::any_of(vec.begin(), vec.end(), isOdd) == true);
    assert(std::any_of(vec.begin(), vec.end(), isSingleDigit) == true);

    // ranges version
    assert(std::ranges::all_of(vec, isSingleDigit) == true);
    assert(std::ranges::none_of(vec, isEven) == false);
    assert(std::ranges::any_of(vec, isOdd) == true);

    return 0;
}
