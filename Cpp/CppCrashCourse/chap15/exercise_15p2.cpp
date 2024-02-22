#include <iostream>
#include <string>

int main(void)
{
    std::string userInput{};

    for (;;)
    {
        std::cin >> userInput;
        if (userInput == "quit")
        {
            std::cout << "Quit the program!" << std::endl;
            break;
        }

        std::string reversedInput(userInput.crbegin(), userInput.crend());
        if (userInput == reversedInput)
        {
            std::cout << "Palindrome!" << std::endl;
        }
        else
        {
            std::cout << "Not Palindrome." << std::endl;
        }
    }
}