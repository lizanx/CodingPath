#include <print>
#include <utility>

namespace
{
    namespace dflt
    {
        namespace impl
        {
            template <typename T>
            concept HasADL = requires(T v) { DoSomething(v); };

            struct DoSomethingFn
            {
                // Has custom impl, just call it.
                template <typename T>
                void operator()(T &&arg) const
                    requires HasADL<T>
                {
                    std::println("Calling custom 'DoSomething' from 'DoSomethingFn'");
                    DoSomething(std::forward<T>(arg));
                }

                // No custom impl, use the default impl.
                template <typename T>
                void operator()(T &&arg) const
                    requires(!HasADL<T>)
                {
                    std::println("Default impl from 'DoSomethingFn'");
                }
            };
        }

        inline namespace var
        {
            constexpr inline auto DoSomething = impl::DoSomethingFn{};
        }
    }

    namespace lib
    {
        struct X
        {
            friend void DoSomething(const X &)
            {
                std::println("X -> friend DoSomething");
            }
        };
    }

    namespace dflt
    {
        struct Y
        {
            friend void DoSomething(const Y &)
            {
                std::println("Y -> friend DoSomething");
            }
        };
    }
}

int main()
{
    int a{};
    lib::X x{};
    dflt::Y y{};

    std::println("===dflt::DoSomething(a)===");
    dflt::DoSomething(a);

    std::println("===dflt::DoSomething(x)===");
    dflt::DoSomething(x);

    std::println("===dflt::DoSomething(y)===");
    dflt::DoSomething(y);

    std::println("===DoSomething(x)===");
    DoSomething(x);

    std::println("===DoSomething(y)===");
    DoSomething(y);

    return 0;
}
