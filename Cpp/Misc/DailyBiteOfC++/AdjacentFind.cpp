#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> strVec{"a", "aa", "bb", "bb", "cc", "c"};

    auto iter = std::adjacent_find(strVec.begin(), strVec.end());
    if (iter == strVec.end())
        std::cout << "Failed to find pair of the same value\n";
    else
        std::cout << "First pair of the same value: " << *iter << ", " << *(iter + 1) << "\n";

    iter = std::adjacent_find(strVec.begin(), strVec.end(), [](const std::string &left, const std::string &right)
                              { return left.length() == right.length(); });
    if (iter == strVec.end())
        std::cout << "Failed to find pair of the same length\n";
    else
        std::cout << "First pair of the same length: " << *iter << ", " << *(iter + 1) << "\n";
}
