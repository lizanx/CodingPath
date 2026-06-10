#include <print>
#include <source_location>
#include <string_view>

namespace
{
    // To capture source location at caller site, use the default argument.
    void Log(std::string_view msg, std::source_location caller = std::source_location::current())
    {
        std::println("[{}:{}/{}] {} \"{}\"\n",
                     caller.file_name(), caller.line(), caller.column(), caller.function_name(), msg);
    }
}

int main()
{
    Log("Hello");

    []()
    { Log("Lambda"); }();

    struct X
    {
        X()
        {
            Log("X::ctor");
        }

        ~X()
        {
            Log("X::dtor");
        }
    };

    X x{};

    return 0;
}
