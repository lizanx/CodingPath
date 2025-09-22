#include <iostream>
#include <stdexcept>
#include <string>

namespace
{
    void skip_to_int(std::istream &input)
    {
        if (input.fail())
        {
            input.clear();
        }
        char ch{};
        while (input >> ch && !std::isdigit(ch))
        {
        }
        if (input)
        {
            input.unget();
            return;
        }
        throw std::runtime_error{"Bad input!"};
    }

    int get_int(std::istream &input)
    {
        int i{};
        while (true)
        {
            if (input >> i)
                return i;
            std::cerr << "Sorry, that's not a number, please try again.\n";
            skip_to_int(input);
        }
    }

    int get_int(int lowerBound, int higherBound, const std::string &prompt, const std::string &errMsg)
    {
        std::cout << prompt << "\n";
        while (true)
        {
            int i = get_int(std::cin);
            if (i >= lowerBound && i <= higherBound)
                return i;
            std::cerr << errMsg << "\n";
        }
    }
}

int main(int argc, char *argv[])
{
    try
    {
        int n = get_int(1, 10,
                        "Please enter a number in range [1, 10]:", "The entered number is out of range!");
        std::cout << "Successfully get number " << n << "\n";
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "Failed, error: " << e.what() << "\n";
    }
    catch (...)
    {
        std::cerr << "Unknown error!\n";
    }
}
