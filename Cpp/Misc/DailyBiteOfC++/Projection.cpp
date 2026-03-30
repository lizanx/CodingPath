#include <algorithm>
#include <cassert>
#include <ranges>
#include <vector>

namespace
{
    struct User
    {
        int id;
        std::string name;
    };
}

int main()
{
    using namespace std::literals;
    std::vector<User> users{
        {3, "User1"},
        {1, "User2"},
        {7, "User3"},
        {12, "User4"},
    };
    std::ranges::sort(users, std::ranges::less{}, &User::id);
    assert(users[0].id == 1);
    assert(users[1].id == 3);
    assert(users[2].id == 7);
    assert(users[3].id == 12);
    auto iter = std::ranges::find(users, "User3", &User::name);
    assert(iter != users.end() && iter->name == "User3" && iter->id == 7);

    std::vector<int> first{1, 2, 3, 4};
    std::vector<int> second{1, 2, 3, 4};
    std::vector<int> out{};
    std::ranges::transform(first, second, std::back_inserter(out), [](int left, int right)
                           { return left * right; }, [](int left)
                           { return left + 10; }, [](int right)
                           { return right / 2; });
    assert(out[0] == 0);
    assert(out[1] == 12);
    assert(out[2] == 13);
    assert(out[3] == 28);

    return 0;
}
