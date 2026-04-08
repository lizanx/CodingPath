#include <print>
#include <ranges>
#include <vector>

int main()
{
    std::vector<int> v1{1, 2, 3, 4};
    std::vector<double> v2{9.1, 9.2, 9.3, 9.4, 9.5};
    std::vector<std::string> v3{"a", "b", "c", "d", "e", "f"};

    auto zipFunc = [](int i, double d, const std::string &s)
    {
        return i + d + (s[0] - 'a');
    };
    for (auto val : std::views::zip_transform(zipFunc, v1, v2, v3))
    {
        std::println("value: {}", val);
    }

    return 0;
}
