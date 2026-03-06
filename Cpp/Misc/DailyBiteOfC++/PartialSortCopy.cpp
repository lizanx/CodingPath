#include <algorithm>
#include <cassert>
#include <forward_list>
#include <print>
#include <string>
#include <string_view>
#include <vector>

int main()
{
    std::forward_list<std::string> names{
        "Emma", "Liam", "Zara", "Ethan", "Aria", "Mateo", "Ivy", "Finn",
        "Luna", "Kai", "Mila", "Oscar", "Ruby", "Levi", "Nora"};
    {
        std::vector<std::string> out(3);
        std::partial_sort_copy(names.begin(), names.end(), out.begin(), out.end());
        assert(out[0] == std::string{"Aria"});
        assert(out[1] == std::string{"Emma"});
        assert(out[2] == std::string{"Ethan"});
    }
    {
        std::vector<std::string> out(5);
        std::partial_sort_copy(names.begin(), names.end(), out.begin(), out.end(), std::greater{});
        assert(out[0] == std::string{"Zara"});
        assert(out[1] == std::string{"Ruby"});
        assert(out[2] == std::string{"Oscar"});
        assert(out[3] == std::string{"Nora"});
        assert(out[4] == std::string{"Mila"});
    }
    {
        std::vector<std::string> out(3);
        auto length = [](const std::string &s)
        { return s.length(); };
        std::ranges::partial_sort_copy(names, out, std::greater{}, length, length);
        assert(out[0] == std::string{"Oscar"});
        assert(out[1] == std::string{"Mateo"});
        assert(out[2] == std::string{"Ethan"});
    }
    {
        std::vector<std::string_view> out(3);
        // Two projections separately for src/dst ranges.
        auto length = [](const std::string &s)
        { return s.length(); };
        auto viewLength = [](const std::string_view &s)
        { return s.length(); };
        std::ranges::partial_sort_copy(names, out, std::greater{}, length, viewLength);
        assert(out[0] == "Oscar");
        assert(out[1] == "Mateo");
        assert(out[2] == "Ethan");
    }

    return 0;
}
