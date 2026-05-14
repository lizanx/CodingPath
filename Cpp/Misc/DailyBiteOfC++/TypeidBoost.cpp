#include <boost/type_index.hpp>
#include <print>
#include <unordered_map>
#include <string>
#include <vector>

namespace
{
    class Base
    {
    public:
        virtual void VirtualFunc()
        {
        }
    };
    class Derived : public Base
    {
    public:
        void VirtualFunc() override
        {
        }
    };

    void Inspector(Base &b)
    {
        std::println("[{}] {}", __PRETTY_FUNCTION__, boost::typeindex::type_id_runtime(b).pretty_name());
    }
}

int main()
{
    int x{20};
    std::println("x -> {}", boost::typeindex::type_id<decltype(x)>().pretty_name());

    double y{2.0};
    std::println("y -> {}", boost::typeindex::type_id<decltype(y)>().pretty_name());

    Base b{};
    Derived d{};
    Inspector(b);
    Inspector(d);

    std::println("Without cv qualifier(default): {}", boost::typeindex::type_id<const int>().pretty_name());
    std::println("With cv qualifier: {}", boost::typeindex::type_id_with_cvr<const int>().pretty_name());

    using nestedType = std::unordered_map<int, std::vector<std::string>>;
    std::println("nestedType -> {}", boost::typeindex::type_id<nestedType>().pretty_name());

    return 0;
}
