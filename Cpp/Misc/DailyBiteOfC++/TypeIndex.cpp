#include <print>
#include <string>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>

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

    // Only polymorphiyc types can store runtime type info, otherwise the stored type is static compile-time info
    class X
    {
    };
    class Y : public X
    {
    };

    // std::type_index is a wrapper of std::type_info
    // type_info cannot be copied/assigned/compared-with-less-or-greater, it only supports ==/!=
    // to use type info as map keys, use type_index instead of type_info
    std::unordered_map<std::type_index, std::string> g_typeNames{
        {typeid(int), "int"},
        {typeid(double), "double"},
        {typeid(Base), "Base"},
        {typeid(Derived), "Derived"},
        {typeid(X), "X"},
        {typeid(Y), "Y"},
    };

    void Inspector(const Base &obj)
    {
        auto iter = g_typeNames.find(typeid(obj));
        if (iter != g_typeNames.end())
            std::println("Inspected '{}'", iter->second);
        else
            throw std::runtime_error{std::format("Unknown type '{}'", typeid(obj).name())};
    }

    // Only polymorphiyc types can store runtime type info, otherwise the stored type is static compile-time info.
    // Since X/Y aren't polymorphic, here 'typeid(obj)' will always return type info of 'X'.
    void InspectFailure(const X &obj)
    {
        auto iter = g_typeNames.find(typeid(obj));
        if (iter != g_typeNames.end())
            std::println("[{}] Inspected '{}'", __FUNCTION__, iter->second);
        else
            throw std::runtime_error{std::format("[{}] Unknown type '{}'", __FUNCTION__, typeid(obj).name())};
    }
}

int main()
{
    std::println("Type name of integer: {}", g_typeNames.at(typeid(int)));
    std::println("Type name of double: {}", g_typeNames.at(typeid(double)));

    Base b{};
    Inspector(b);
    Derived d{};
    Inspector(d);

    X x{};
    Y y{};
    InspectFailure(x);
    InspectFailure(y);

    return 0;
}
