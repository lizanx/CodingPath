#include <algorithm>
#include <print>
#include <vector>

namespace
{
    void PrintVector(const std::vector<int> &vec, std::string_view msg)
    {
        std::print("{}: ", msg);
        for (int n : vec)
            std::print("{} ", n);
        std::println();
    }
}

int main()
{
    std::vector<int> data{1, 2, 3, 4, 5, 6, 7};
    PrintVector(data, "Original Vector");

    std::rotate(data.begin(), std::next(data.begin()), data.end());
    PrintVector(data, "Rotate by 1");

    std::rotate(data.begin(), std::next(data.begin(), 3), data.end());
    PrintVector(data, "Rotate by 3");

    return 0;
}
