#include <format>
#include <iostream>
#include <optional>
#include <ranges>
#include <string>

namespace
{
    struct Package
    {
        std::string Name{};
        unsigned int MajorVersion{};
        unsigned int MinorVersion{};
        unsigned int PatchVersion{};
    };

    struct ProgrammingLanguage
    {
        std::string Name{};
        unsigned int MajorVersion{};
        std::optional<unsigned int> MinorVersion{};
        std::optional<unsigned int> PatchVersion{};
    };
}

namespace std
{
    template <>
    struct formatter<Package>
    {
    public:
        constexpr auto parse(format_parse_context &ctx)
        {
            return _strFormatter.parse(ctx);
        }

        auto format(Package &package, format_context &ctx) const
        {
            string formatted = std::format("{}({}.{}.{})", package.Name, package.MajorVersion,
                                           package.MinorVersion, package.PatchVersion);
            return _strFormatter.format(formatted, ctx);
        }

    private:
        formatter<string> _strFormatter{};
    };

    template <>
    struct formatter<ProgrammingLanguage>
    {
    public:
        constexpr auto parse(format_parse_context &ctx) -> decltype(ctx.begin())
        {
            auto iter = ranges::find(ctx, '}');
            if (iter == ctx.end())
                throw format_error{"Invalid format for ProgrammingLanguage"};
            _format = string{ctx.begin(), iter};
            return iter;
        }

        auto format(const ProgrammingLanguage &pl, format_context &ctx) const -> decltype(ctx.out())
        {
            auto out = ctx.out();
            if (_format.empty())
                return format_to(out, "{}({})", pl.Name, pl.MajorVersion);
            for (auto iter = _format.begin(); iter != _format.end(); ++iter)
            {
                if (*iter == '%')
                {
                    ++iter;
                    if (iter == _format.end())
                        throw format_error{"Invalid format, no format specifier following '%'"};
                    switch (*iter)
                    {
                    case '%':
                        out = format_to(out, "%");
                        break;
                    case 'l':
                        out = format_to(out, "{}", pl.Name);
                        break;
                    case 'v':
                        out = format_to(out, "{}", pl.MajorVersion);
                        if (pl.MinorVersion)
                        {
                            out = format_to(out, ".{}", pl.MinorVersion.value());
                            if (pl.PatchVersion)
                                out = format_to(out, ".{}", pl.PatchVersion.value());
                        }
                        break;
                    case 'm':
                        out = format_to(out, "{}", pl.MajorVersion);
                        break;
                    case 'n':
                        if (!pl.MinorVersion)
                            throw format_error{"Minor version not existent"};
                        out = format_to(out, "{}", pl.MinorVersion.value());
                        break;
                    case 'p':
                        if (!pl.PatchVersion)
                            throw format_error{"Patch version not existent"};
                        out = format_to(out, "{}", pl.PatchVersion.value());
                        break;
                    default:
                        throw format_error{"Unknown format specifier!"};
                        break;
                    }
                }
                else
                {
                    out = format_to(out, "{}", *iter);
                }
            }
            return out;
        }

    private:
        string _format{};
    };
}

int main(int argc, char *argv[])
{
    using namespace std::string_literals;

    std::cout << "=== Packages ===\n";
    Package p1{"SkiaSharp", 1, 2, 3};
    std::cout << std::format("{}", p1) << '\n';
    Package p2{"Pillow", 10, 3, 7};
    std::cout << std::format("{}", p2) << '\n';

    std::cout << "=== Programming Languages ===\n";
    ProgrammingLanguage Cpp20{"C++", 20};
    std::cout << std::format("{}", Cpp20) << '\n';
    std::cout << std::format("{:%l - %v}", Cpp20) << '\n';
    std::cout << std::format("Version {:%v} of {:%l}", Cpp20, Cpp20) << '\n';
    ProgrammingLanguage Python3{"Python", 3};
    std::cout << std::format("{}", Python3) << '\n';
    std::cout << std::format("{:%l-%v}", Python3, Python3) << '\n';
    ProgrammingLanguage Python3_14{"Python", 3, 14};
    std::cout << std::format("{}", Python3_14) << '\n';
    std::cout << std::format("{:%l-%v}", Python3_14, Python3_14) << '\n';
    ProgrammingLanguage Python3_14_1{"Python", 3, 14, 1};
    std::cout << std::format("{}", Python3_14_1) << '\n';
    std::cout << std::format("{:%l-%v}", Python3_14_1, Python3_14_1) << '\n';
}
