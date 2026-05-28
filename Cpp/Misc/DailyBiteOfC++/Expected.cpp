#include <cassert>
#include <expected>
#include <print>
#include <string>
#include <system_error>

namespace
{
    std::expected<std::string, std::error_code> Fn(bool ok)
    {
        if (ok)
            return "Hello World!";
        return std::unexpected{std::make_error_code(std::errc::invalid_argument)};
    }
}

int main()
{
    {
        // Similar interface to std::optional
        std::expected<int, int> v{10};
        assert(v.has_value());
        assert(v.value() == 10);
        assert(*v == 10);
    }

    {
        // To distinguish the error, it has to be wrapped in std::unexpected
        std::expected<int, int> e = std::unexpected{10};
        assert(!e.has_value());
        assert(e.error() == 10);
        // *e throws
    }

    {
        // Default initialized to a valid value, always contains either a result or an error
        std::expected<int, int> m{};
        assert(m.has_value());
        assert(m.value() == 0);
        assert(*m == 0);
    }

    {
        // If the result type cannot be default constructed,
        // the resulting std::expected cannot be default constructed either.
        struct NonDefaultConstructible
        {
            NonDefaultConstructible(int x)
            {
            }
        };

        // std::expected<NonDefaultConstructible, int> m{};   // won't compile
        std::expected<NonDefaultConstructible, int> n{20}; // ok
        assert(n.has_value());
    }

    return 0;
}
