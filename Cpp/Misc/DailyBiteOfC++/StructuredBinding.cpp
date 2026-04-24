#include <cassert>
#include <print>
#include <string>
#include <unordered_set>

namespace
{
    struct UserType
    {
        int a;
        double b;
        std::string c;
    };
}

int main()
{
    std::unordered_set<int> data{1, 2, 3, 4, 5};
    if (auto [iter, inserted] = data.insert(4); inserted)
    {
        std::println("Inserted, *iter = {}", *iter);
    }
    else
    {
        std::println("Already existent, *iter = {}", *iter);
    }

    {
        std::pair<int, int> p{10, 20};
        auto [i, j] = p; // Capture by copy
        assert((i == 10 && j == 20));
        i = 1;
        j = 2;
        assert((p.first == 10 && p.second == 20));
        auto &[m, n] = p; // Capture by reference
        assert((m == 10 && n == 20));
        m = 1;
        n = 2;
        assert((p.first == 1 && p.second == 2));
    }

    {
        const std::pair<int, int> p{10, 20};
        auto &[i, j] = p; // Capture by reference
        assert((i == 10 && j == 20));
        assert((std::is_same_v<decltype((i)), const int &>));
        assert((std::is_same_v<decltype((j)), const int &>));
        // i = 1; // Cannot compile
        // j = 2; // Cannot compile
    }

    {
        UserType user{1, 2.2, "Hello world"};
        auto [x, y, z] = user;
        assert(x == 1);
        assert(y == 2.2);
        assert(z == "Hello world");
    }

    return 0;
}
