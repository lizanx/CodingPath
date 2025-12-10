#include <expected>
#include <iostream>
#include <random>
#include <stdexcept>

namespace
{
    enum class Error
    {
        TooLarge,
        TooSmall,
        NotEven,
    };

    auto GetSingleDigitEvenNumber(int min, int max) noexcept -> std::expected<int, Error>
    {
        static std::random_device rdev{};
        std::mt19937 eng{rdev()};
        std::uniform_int_distribution dist{min, max};
        if (int num = dist(eng); num < 0)
            return std::unexpected{Error::TooSmall};
        else if (num >= 10)
            return std::unexpected{Error::TooLarge};
        else if (num % 2 != 0)
            return std::unexpected{Error::NotEven};
        else
            return num;
    }

    auto PrintError(Error err) -> void
    {
        switch (err)
        {
        case Error::TooLarge:
            std::cout << "Error: the number is too large.\n";
            break;
        case Error::TooSmall:
            std::cout << "Error: the number is too small.\n";
            break;
        case Error::NotEven:
            std::cout << "Error: the number is within valid range, but not an even number.\n";
            break;
        default:
            throw std::runtime_error{std::format("Unknown error {}", static_cast<int>(err))};
        }
    }
}

int main(int argc, char *argv[])
{
    std::cout << "========== Round1 ==========\n\n";
    for (size_t i{}; i < 10; ++i)
    {
        auto result = GetSingleDigitEvenNumber(-10, 20);
        if (result)
            std::cout << "-> Successfully got " << *result << ".\n";
        else
            PrintError(result.error());
    }
    std::cout << "\n========== Round2 ==========\n\n";
    for (size_t i{}; i < 10; ++i)
    {
        auto result = GetSingleDigitEvenNumber(-5, 10)
                          .transform([](int n)
                                     {
                                        std::cout << "Got " << n << "\n";
                                        return n * n; })
                          .and_then([](int n)
                                    {
                                        if (n > 10)
                                            return std::expected<int, Error>{n + 2};
                                        else
                                            return std::expected<int, Error>{n + 4}; });
        if (result)
            std::cout << "-> Successfully transformed to " << *result << ".\n";
        else
            PrintError(result.error());
    }
}
