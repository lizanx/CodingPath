#include <iostream>
#include <string>
#include <cstdlib>

int main()
{
    std::string command{ "ping -c 3 www.qq.com" };

    const auto result = std::system(command.c_str());

    std::cout << "The command [" << command
        << "] returns " << result << std::endl;
}
