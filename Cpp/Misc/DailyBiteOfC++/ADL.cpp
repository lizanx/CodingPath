#include <print>

namespace
{
    namespace lib
    {
        struct X
        {
            friend void AdlOnly(const X &)
            {
                std::println("AdlOnly");
            }
        };

        X operator+(const X &, const X &)
        {
            std::println("lib::operator+(const X&, const X&)");
            return {};
        }

        void operate(const X &)
        {
            std::println("lib::operate(const X&)");
        }

        void ShutOff(const X &)
        {
            std::println("lib::ShutOff(const X&)");
        }

        constexpr inline auto OnlyExplicit = [](const X &)
        {
            std::println("lib::OnlyExplicit");
        };
    }

    constexpr inline auto ShutOff = [](auto &&)
    {
        std::println("::ShutOff");
    };
}

int main()
{
    lib::X a{}, b{};

    std::println("--- ---");
    a = a + b;
    a = lib::operator+(a, b);

    std::println("--- ---");
    operate(a);
    lib::operate(b);

    std::println("--- ---");
    ShutOff(a);
    lib::ShutOff(b);

    std::println("--- ---");
    AdlOnly(a);
    // lib::AdlOnly(b); // won't compile

    std::println("--- ---");
    // Non-function entities don't participate in ADL.
    // OnlyExplicit(a); // won't compile
    lib::OnlyExplicit(b);

    return 0;
}
