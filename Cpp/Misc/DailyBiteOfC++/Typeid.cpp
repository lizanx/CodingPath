#include <print>
#include <string_view>
#include <typeinfo>

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

    void Inspector(const Base &obj)
    {
        if (typeid(obj) == typeid(Base))
            std::println("Inspected Base");
        else if (typeid(obj) == typeid(Derived))
            std::println("Inspected Derived");
        else
            throw std::runtime_error{std::format("Unknown type: {}", typeid(obj).name())};
    }
}

int main()
{
    std::string_view intName = typeid(int).name();
    std::string_view doubleName = typeid(double).name();
    std::string_view stringName = typeid(const char *).name();
    std::println("Names: int -> {}, double -> {}, const char* -> {}",
                 intName, doubleName, stringName);

    Base b{};
    Inspector(b);
    Derived d{};
    Inspector(d);

    return 0;
}
