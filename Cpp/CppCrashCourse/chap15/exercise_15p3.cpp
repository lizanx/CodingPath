#include <iostream>
#include <string>
#include <algorithm>

int main(void)
{
    std::string userInput{};
    std::string vowels{"aeiou"};

    for (;;)
    {
        std::cin >> userInput;
        if (userInput == "quit")
        {
            std::cout << "Quit the program!" << std::endl;
            break;
        }

        std::cout << "Number of vowel: "
            << std::count_if(userInput.crbegin(), userInput.crend(), [&vowels](char c){
                return vowels.find(c) != std::string::npos;
            })
            << std::endl;
    }
}
