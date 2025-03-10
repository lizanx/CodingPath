#include <exception>
#include <iostream>
#include <stdexcept>

namespace
{
    void inner_throw()
    {
        std::cout << "inner_throw...\n";
        throw std::runtime_error{"Inner throw error"};
    }

    void middle_throw()
    {
        std::cout << "middle_throw...\n";
        try
        {
            inner_throw();
        }
        catch (const std::exception &e)
        {
            std::throw_with_nested(std::runtime_error{"Middle throw error"});
        }
    }

    void outer_throw()
    {
        std::cout << "outer_throw...\n";
        try
        {
            middle_throw();
        }
        catch (const std::exception &e)
        {
            std::throw_with_nested(std::runtime_error{"Outer throw error"});
        }
    }

    void print_nested_exceptions(const std::exception &e, int depth = 0)
    {
        std::cout << std::string(2 * (depth + 1), '-') << e.what() << "\n";
        try
        {
            std::rethrow_if_nested(e);
        }
        catch (const std::exception &innerException)
        {
            print_nested_exceptions(innerException, depth + 1);
        }
    }

} // namespace

int main()
{
    try
    {
        outer_throw();
    }
    catch (std::exception &e)
    {
        print_nested_exceptions(e);
    }
}
