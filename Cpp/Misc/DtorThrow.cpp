#include <iostream>

// Since C++11, destructors are "noexcept" by default, thus throwing in a dtor will cause "std::terminate" immediately.
// If you explicitly mark the dtor as "noexcept(false)", it can throw and the exception can be caught.
// However, if the throw happens during stack unwinding, "std::terminate" will be called.
// To summarize, don't throw in dtors, use logging or error flag.(Unless you can make sure it never throws during stack unwinding)

namespace
{
    void demo1()
    {
        struct A
        {
            A() = default;
            ~A()
            {
                throw std::runtime_error{"A::~A()"};
            }
        };

        try
        {
            A obj{};
        }
        catch (const std::exception &e)
        {
            std::cout << "demo1: " << e.what() << '\n';
        }
    }

    void demo2()
    {
        struct B
        {
            B() = default;
            ~B() noexcept(false)
            {
                throw std::runtime_error{"B::~B()"};
            }
        };

        try
        {
            B obj{};
        }
        catch (const std::exception &e)
        {
            std::cout << "demo2: " << e.what() << '\n';
        }
    }

    void demo3()
    {
        struct C
        {
            C() = default;
            ~C() noexcept(false)
            {
                throw std::runtime_error{"A::~A()"};
            }
        };

        try
        {
            C obj{};
            throw std::runtime_error{"Some other exception."};
        }
        catch (const std::exception &e)
        {
            std::cout << "demo3: " << e.what() << '\n';
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: program <1|2|3>\n";
        exit(EXIT_FAILURE);
    }

    switch (argv[1][0])
    {
    case '1':
        demo1();
        break;
    case '2':
        demo2();
        break;
    case '3':
        demo3();
        break;
    default:
        std::cerr << "Usage: program <1|2|3>\n";
        exit(EXIT_FAILURE);
    }

    std::cout << "main finished\n";

    return 0;
}
