/*
 * This demo comes from the blog post https://mropert.github.io/2025/11/17/enum_class_error_codes_part2/.
 */

#include <iostream>
#include <random>

namespace
{
    struct Result
    {
        enum class Value
        {
            Success = 0,
            SomeError,
            SomeOtherError,
        };
        using enum Value;

        constexpr Result(Value value) : v{value}
        {
        }

        constexpr explicit operator bool() const
        {
            return v == Success;
        }

        Value v;
    };

    inline constexpr bool operator==(const Result &lhs, const Result &rhs) noexcept
    {
        return lhs.v == rhs.v;
    }

    inline constexpr bool operator!=(const Result &lhs, const Result &rhs) noexcept
    {
        return lhs.v != rhs.v;
    }

    constexpr const char *Stringify(const Result &r) noexcept
    {
        switch (r.v)
        {
        case Result::Success:
            return "Success";
        case Result::SomeError:
            return "SomeError";
        case Result::SomeOtherError:
            return "SomeOtherError";
        default:
            return "Unknown";
        }
    }

    Result DemoFunc() noexcept
    {
        static std::random_device rdev{};
        std::mt19937 eng{rdev()};
        std::uniform_int_distribution dist{0, 10};
        if (int v = dist(eng); v < 3)
            return Result::Success;
        else if (v < 6)
            return Result::SomeError;
        else
            return Result::SomeOtherError;
    }
}

int main(int argc, char *argv[])
{
    for (size_t i{}; i < 20; ++i)
    {
        if (Result r = DemoFunc(); r)
            std::cout << "++Good call: " << Stringify(r) << "\n";
        else
            std::cout << "--Bad call: " << Stringify(r) << "\n";
    }

    return 0;
}
