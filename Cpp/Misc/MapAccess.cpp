#include <iostream>
#include <map>
#include <string>

namespace
{
    using std::string;

    std::map<string, int> digits{
        {"Zero", 0},
        {"One", 1},
        {"Two", 2},
        {"Three", 3},
        {"Four", 4},
        {"Five", 5},
        {"Six", 6},
        {"Seven", 7},
        {"Eight", 8},
        {"Nine", 9},
    };
}

int main(int argc, char *argv[])
{
    // operator[]
    std::cout << "=== Access via operator[] ===\n";
    std::cout << "One: " << digits["One"] << "\n"
              << "Eleven: " << digits["Eleven"] << "\n"; // This implicitly inserts {"Eleven", 0} into the map.

    // at()
    std::cout << "=== Access via at() ===\n";
    std::cout << "Two: " << digits.at("Two") << "\n";
    try
    {
        std::cout << "Twelve: " << digits.at("Twelve") << "\n"; // Throws if the key doesn't exist.
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "!!! ERROR: 'digits' has no key 'Twelve'\n";
    }

    // find()
    std::cout << "=== Access via find() ===\n";
    std::cout << "Three: " << digits.find("Three")->second << "\n";
    auto iter = digits.find("Thirteen");
    if (iter != digits.end())
        std::cout << "Thirteen: " << iter->second << "\n";
    else
        std::cout << "Cannot find key 'Thirteen' in 'digits'\n";
}
