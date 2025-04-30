#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <string>

extern int StartProgram();

TEST(CompleteProgram, ProgramStdOutputEqualExpectation)
{
    using std::string;

    string expectedOutput{"3 + 5 = 8\n3 * 5 = 15\n"};
    // Redirect output buffer
    std::stringstream outputStream{};
    auto originalCoutBuffer = std::cout.rdbuf(outputStream.rdbuf());
    // Run program
    StartProgram();
    // Get program output
    string programOutput = outputStream.str();
    // Redirect std output buffer back
    std::cout.rdbuf(originalCoutBuffer);
    // Check result
    EXPECT_EQ(expectedOutput, programOutput);
}
