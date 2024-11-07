#include <iostream>

namespace outer_ns
{
    void f()
    {
        std::cout << "outer_ns::f()\n";
    }

    inline namespace inner_ns_default
    {
        void g()
        {
            std::cout << "outer_ns::inner_ns_default::g()\n";
        }
    }

    namespace inner_ns_1
    {
        void g()
        {
            std::cout << "outer_ns::inner_ns_1::g()\n";
        }
    }

    namespace inner_ns_2
    {
        void g()
        {
            std::cout << "outer_ns::inner_ns_2::g()\n";
        }
    }

    namespace [[deprecated]] inner_ns_deprecated
    {
        void g()
        {
            std::cout << "This function is deprecated!!! You shouldn't use it.\n";
        }
    }
}

namespace outer_ns::inner_ns_3
{
    void g()
    {
        std::cout << "outer_ns::inner_ns_3::g()\n";
    }
}

int main()
{
    // Alias
    namespace ns = outer_ns;

    ns::f();
    ns::g(); // This calls "ns::inner_ns_default::g()" because "inner_ns_default" is inline
    ns::inner_ns_default::g();
    ns::inner_ns_1::g();
    ns::inner_ns_2::g();
    ns::inner_ns_3::g();
    ns::inner_ns_deprecated::g(); // This one causes compiler warning since the namespace is marked 'deprecated'

    return EXIT_SUCCESS;
}
