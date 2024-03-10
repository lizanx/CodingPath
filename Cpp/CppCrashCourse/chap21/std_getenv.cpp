#include <iostream>
#include <string>
#include <cstdlib>

int main()
{
    std::string envVarName{ "PATH" };
    std::string envPath{ std::getenv(envVarName.c_str()) };
    std::cout << "The environment variable "
        << envVarName << ":\n"
        << envPath << std::endl;
}
