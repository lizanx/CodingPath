#include <iostream>
#include <map>
#include <cstring>

int main(int argc, char *argv[])
{
    std::map<size_t, int> length_map{};

    for (size_t i{ 1 }; i < argc; i++)
    {
        auto len = strlen(argv[i]);
        if (length_map.contains(len))
        {
            length_map[len]++;
        }
        else
        {
            length_map[len] = 1;
        }
    }

    for (const auto& [len, cnt] : length_map)
    {
        std::cout << "Length " << len << "\t:" << std::string(cnt, '*') << '\n';
    }
}