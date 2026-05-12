#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

namespace
{
    struct Item
    {
        int m_id;
        std::string m_label;
    };
}

int main()
{
    {
        std::vector<int> v1{1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::vector<int> v2{2, 3, 4};
        std::vector<int> v3{3, 5, 8};
        std::vector<int> v4{4, 4};
        assert(std::includes(v1.begin(), v1.end(), v2.begin(), v2.end()));
        assert(std::includes(v1.begin(), v1.end(), v3.begin(), v3.end()));
        assert(!std::includes(v1.begin(), v1.end(), v4.begin(), v4.end()));
    }

    {
        std::vector<Item> inventory{
            {0, "Banana"},
            {3, "Apple"},
            {4, "Cherry"},
            {5, "Melon"}};
        std::vector<Item> order{
            {3, "Apple"},
            {5, "Melon"}};
        bool allInStock = std::ranges::includes(inventory, order, {}, &Item::m_id, &Item::m_id);
        assert(allInStock);
    }

    return 0;
}
