#include <array>
#include <iostream>
#include <span>
#include <vector>

static void DisplayContent(std::span<int> span)
{
    std::cout << "------------------------------\n";
    std::cout << "Size: " << span.size() << "\n";
    for (int i : span)
    {
        std::cout << "Span Data: " << i << "\n";
    }
    std::cout << "------------------------------\n";
}

int main()
{
    int arr[3]{1, 2, 3};
    std::array<int, 3> stdArr{4, 5, 6};
    std::vector<int> vec{7, 8, 9, 10};

    DisplayContent(arr);
    DisplayContent(stdArr);
    DisplayContent(vec);
}
