#include <algorithm>
#include <iostream>
#include <string>

namespace
{
    std::vector<int> intVec{1, 4, 8, 9, 15};
    std::vector<int> intVec2{2, 3, 7, 7, 11, 22};
    std::vector<std::string> strVec{"C++", "C#", "Python", "Zig"};

    template <typename T>
    void PrintVector(const std::vector<T> &vec)
    {
        for (const T &element : vec)
            std::cout << element << ", ";
        std::cout << '\n';
    }
}

int main(int argc, char *argv[])
{
    std::for_each(intVec.begin(), intVec.end(), [](int &n)
                  { n *= 2; });
    std::cout << "After for_each, intVec: ";
    PrintVector(intVec);

    auto isEven = [](int n)
    { return n % 2 == 0; };
    auto isOdd = [](int n)
    { return n % 2 != 0; };
    std::cout << "All numbers in intVec are even: "
              << std::all_of(intVec.cbegin(), intVec.cend(), isEven)
              << "\n";
    std::cout << "Any number in intVec is odd: "
              << std::any_of(intVec.cbegin(), intVec.cend(), isOdd)
              << "\n";
    std::cout << "No numbers in intVec is odd: "
              << std::none_of(intVec.cbegin(), intVec.cend(), isOdd)
              << "\n";

    std::cout << "Count of odd numbers in intVec2: "
              << std::count_if(intVec2.cbegin(), intVec2.cend(), isOdd)
              << "\n";

    std::cout << "First adjacent same numbers in intVec2: "
              << *std::adjacent_find(intVec2.cbegin(), intVec2.cend())
              << "\n";
}
