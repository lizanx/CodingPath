#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> longWords{}, shortWords{};

    std::partition_copy(std::istream_iterator<std::string>{std::cin},
                        std::istream_iterator<std::string>{},
                        std::back_inserter(longWords),
                        std::back_inserter(shortWords),
                        [](const std::string &s)
                        {
                            return s.length() >= 5;
                        });

    std::cout << "===== Long words =====\n";
    for (const auto &str : longWords)
        std::cout << str << "\n";

    std::cout << "===== Short words =====\n";
    for (const auto &str : shortWords)
        std::cout << str << "\n";
}
