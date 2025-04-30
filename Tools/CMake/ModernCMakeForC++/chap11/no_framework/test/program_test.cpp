#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

extern int StartProgram(int argc, char *argv[]);

void TestProgram()
{
    using std::string;

    string expectedOutput{"3 + 5 = 8\n3 * 5 = 15\n"};
    // Redirect output buffer
    std::stringstream outputStream{};
    auto originalCoutBuffer = std::cout.rdbuf(outputStream.rdbuf());
    // Run program
    char *arguments[] = {"main"};
    StartProgram(1, arguments);
    // Get program output
    string programOutput = outputStream.str();
    // Redirect std output buffer back
    std::cout.rdbuf(originalCoutBuffer);
    // Check result
    if (programOutput != expectedOutput)
        std::exit(1);
}
