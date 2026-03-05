#include <cassert>
#include <print>
#include <string>
#include <variant>

int main()
{
    using std::string;

    std::variant<string, int, double> v{}; // variant is never empty, default initialized to first type.
    assert(std::holds_alternative<string>(v));
    v = 1;
    assert(std::holds_alternative<int>(v));
    int i = std::get<int>(v);
    assert(i == 1);
    int j = std::get<1>(v);
    assert(j == 1);
    try
    {
        double z = std::get<double>(v);
    }
    catch (const std::bad_variant_access &e)
    {
        std::println("Failed to access double, err: {}", e.what());
    }

    class NonDefaultConstructible
    {
    public:
        NonDefaultConstructible(int i) {}
    };
    // std::variant<NonDefaultConstructible, int> vv{}; // cannot compile
    std::variant<NonDefaultConstructible, int> vv1{1};
    assert(std::holds_alternative<int>(vv1));
    std::variant<NonDefaultConstructible, int> vv2{NonDefaultConstructible{2}};
    assert(std::holds_alternative<NonDefaultConstructible>(vv2));
}
