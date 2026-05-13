#include <any>
#include <cassert>
#include <print>
#include <stdexcept>

namespace
{
    struct BasicPayload
    {
    };

    struct ExtendedPayload
    {
    };

    void Function(std::any payload)
    {
        if (payload.type() == typeid(BasicPayload))
            std::println("Basic payload.");
        else if (payload.type() == typeid(ExtendedPayload))
            std::println("Extended payload.");
        else
            throw std::runtime_error{"Unknown payload."};
    }
}

int main()
{
    Function(BasicPayload{});
    Function(ExtendedPayload{});
    try
    {
        Function(10);
    }
    catch (const std::exception &e)
    {
        std::println("Exception: {}", e.what());
    }

    {
        std::any holder{};
        assert(!holder.has_value());

        holder = 42;
        try
        {
            int v = std::any_cast<int>(holder);
            assert(v == 42);

            int *p = std::any_cast<int>(&holder);
            assert(*p == 42);

            double d = std::any_cast<double>(holder);
        }
        catch (const std::bad_any_cast &e)
        {
            std::println("Bad any cast: {}", e.what());
        }
        catch (const std::exception &e)
        {
            std::println("Unknown exception: {}", e.what());
        }
    }

    return 0;
}
