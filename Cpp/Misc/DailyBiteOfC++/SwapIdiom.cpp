#include <algorithm>
#include <print>

namespace
{
    namespace MyNS
    {
        struct A
        {
            friend void swap(A &left, A &right);
        };

        void swap(A &left, A &right)
        {
            std::println("Customized swap for A");
        }

        struct B
        {
        };
    }
}

int main()
{
    MyNS::A a1{}, a2{};
    MyNS::B b1{}, b2{};

    {
        std::println("<------------ 1 ------------>");
        std::swap(a1, a2); // calls std::swap
        std::swap(b1, b2); // calls std::swap
    }

    {
        std::println("<------------ 2 ------------>");
        swap(a1, a2); // calls MyNS::swap(A &, A &)
        // swap(b1, b2); // fails to compile
    }

    {
        std::println("<------------ 3 ------------>");
        using std::swap;
        swap(a1, a2); // calls MyNS::swap(A &, A &)
        swap(b1, b2); // calls std::swap
    }

    {
        std::println("<------------ 4 ------------>");
        std::ranges::swap(a1, a2); // calls MyNS::swap(A &, A &)
        std::ranges::swap(b1, b2); // calls std::swap
    }

    return 0;
}
