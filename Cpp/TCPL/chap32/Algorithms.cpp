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

    intVec = {1, 2, 3, 5, 7};
    intVec2 = {1, 2, 3, 4, 6};
    std::cout << "Two int vecs equal: "
              << std::equal(intVec.cbegin(), intVec.cend(), intVec2.cbegin())
              << "\n";
    auto mismatchPair = std::mismatch(intVec.cbegin(), intVec.cend(), intVec2.cbegin());
    std::cout << "Mismatch point: "
              << *mismatchPair.first << ", " << *mismatchPair.second
              << "\n";

    intVec = {1, 1, 1, 2, 3};
    intVec2 = {1, 2, 3};
    {
        auto iter = std::search(intVec.cbegin(), intVec.cend(), intVec2.cbegin(), intVec2.cend());
        if (iter != intVec.cend())
            std::cout << "intVec2 is sub-sequence of intVec, starting from index " << (iter - intVec.cbegin()) << "\n";
        else
            std::cout << "intVec2 is not sub-sequence of intVec2\n";
    }
    {
        auto iter = std::search_n(intVec.cbegin(), intVec.cend(), 3, 1);
        if (iter != intVec.cend())
            std::cout << "intVec has consecutive three 1s\n";
        else
            std::cout << "intVec doesn't have consecutive three 1s\n";
    }

    intVec = {1, 2, 3};
    intVec2 = {};
    std::transform(intVec.cbegin(), intVec.cend(), std::back_inserter(intVec2), [](int i)
                   { return i * 2; });
    std::cout << "intVec2: ";
    PrintVector(intVec2);
    {
        std::vector<int> intVec3{};
        std::transform(intVec.cbegin(), intVec.cend(),
                       intVec2.cbegin(), std::back_inserter(intVec3), [](int m, int n)
                       { return m + n; });
        std::cout << "intVec3: ";
        PrintVector(intVec3);
    }

    intVec = {1, 5, 8, 12, 43, 56};
    intVec2 = {};
    std::copy(intVec.cbegin(), intVec.cend(), std::back_inserter(intVec2));
    std::cout << "intVec2: ";
    PrintVector(intVec2);
    intVec2 = {};
    std::copy_n(intVec.cbegin(), 3, std::back_inserter(intVec2));
    std::cout << "intVec2: ";
    PrintVector(intVec2);
    intVec2 = {};
    std::copy_if(intVec.cbegin(), intVec.cend(), std::back_inserter(intVec2), [](int n)
                 { return n % 2 == 0; });
    std::cout << "intVec2: ";
    PrintVector(intVec2);

    intVec = {1, 2, 2, 3, 3, 6, 6, 6, 8, 9, 9, 7};
    intVec2 = {};
    {
        auto p = std::unique(intVec.begin(), intVec.end());
        std::cout << "Unique elements: ";
        PrintVector(std::vector<int>(intVec.begin(), p));
        std::cout << "intVec: ";
        PrintVector(intVec);

        intVec = {1, 2, 2, 3, 3, 6, 6, 6, 8, 9, 9, 7};
        std::unique_copy(intVec.begin(), intVec.end(), std::back_inserter(intVec2));
        std::cout << "intVec2: ";
        PrintVector(intVec2);
    }

    intVec = {1, 2, 2, 3, 6, 8, 9, 7};
    intVec2 = {};
    {
        auto p = std::remove(intVec.begin(), intVec.end(), 2);
        PrintVector(std::vector<int>(intVec.begin(), p));
        intVec.erase(p, intVec.end());

        p = std::remove_if(intVec.begin(), intVec.end(), [](int n)
                           { return n % 2 == 0; });
        PrintVector(std::vector<int>(intVec.begin(), p));
    }
    intVec = {1, 2, 2, 3, 6, 8, 9, 7};
    std::replace_if(intVec.begin(), intVec.end(), [](int n)
                    { return n % 2 == 0; }, 0);
    PrintVector(intVec);

    intVec = {1, 2, 3, 4, 5, 6};
    {
        auto p = std::rotate(intVec.begin(), intVec.begin() + 4, intVec.end());
        std::cout << "After rotation, intVec: ";
        PrintVector(intVec);
    }

    intVec = {1, 2, 3, 4, 5, 6};
    {
        auto p = std::partition(intVec.begin(), intVec.end(), [](int n)
                                { return n % 2 == 0; });
        std::cout << "After partition: ";
        PrintVector(std::vector<int>(intVec.begin(), p));
        PrintVector(std::vector<int>(p, intVec.end()));

        intVec = {1, 2, 3, 4, 5, 6};
        p = std::stable_partition(intVec.begin(), intVec.end(), [](int n)
                                  { return n % 2 == 0; });
        std::cout << "After stable partition: ";
        PrintVector(std::vector<int>(intVec.begin(), p));
        PrintVector(std::vector<int>(p, intVec.end()));
    }
}
