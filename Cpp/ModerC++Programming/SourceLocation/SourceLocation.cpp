#include <iostream>
#include <source_location>

void f(std::source_location callerSourceLocation = std::source_location::current())
{
    std::cout << "### Caller ###" << "\n";
    std::cout << "File name: " << callerSourceLocation.file_name() << "\n";
    std::cout << "Function name: " << callerSourceLocation.function_name() << "\n";
    std::cout << "Line number: " << callerSourceLocation.line() << "\n";

    std::cout << "\n### Callee ###" << "\n";
    auto calleeSourceLocation = std::source_location::current();
    std::cout << "File name: " << calleeSourceLocation.file_name() << "\n";
    std::cout << "Function name: " << calleeSourceLocation.function_name() << "\n";
    std::cout << "Line number: " << calleeSourceLocation.line() << "\n";
}

int main()
{
    f();

    return EXIT_SUCCESS;
}
