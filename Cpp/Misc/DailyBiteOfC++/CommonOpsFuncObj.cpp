#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

int main()
{
    auto moduloInt = std::modulus<int>{};
    auto a = moduloInt(10, 4);
    assert(a == 2);

    auto negateInt = std::negate<int>{};
    auto b = negateInt(10);
    assert(b == -10);

    const std::vector<int> data{1, 2, 3, 4, 5};

    std::vector<int> negations{};
    std::ranges::transform(data, std::back_inserter(negations), std::negate{});
    std::cout << "Negations: ";
    for (int n : negations)
        std::cout << n << ' ';
    std::cout << '\n';

    auto sum = std::ranges::fold_left(data, 0, std::plus{});
    assert(sum == 15);

    auto product = std::ranges::fold_left(data, 1, std::multiplies{});
    assert(product == 120);

    return 0;
}
