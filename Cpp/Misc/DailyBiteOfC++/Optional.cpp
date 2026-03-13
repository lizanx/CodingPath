#include <iostream>
#include <optional>

namespace
{
    struct Data
    {
        void Method()
        {
            ++m_value;
        }

        int m_value;
    };

    std::ostream &operator<<(std::ostream &os, const Data &data)
    {
        os << "Data{value = " << data.m_value << "}";
        return os;
    }
}

int main()
{
    std::optional<Data> x{Data{1}};

    {
        if (x != std::nullopt)
        {
            x->Method();
            auto y = *x;
            std::cout << "y: " << y << "\n";
        }
    }

    {
        if (x.has_value())
        {
            auto z = x.value();
            std::cout << "z: " << z << "\n";
        }
    }

    {
        auto a = x.value_or(Data{10});
        std::cout << "a: " << a << "\n";
    }

    {
        x = std::nullopt;
        auto b = x.value_or(Data{20});
        std::cout << "b: " << b << "\n";
    }

    {
        x = Data{1};
        x.reset();
        auto d = x.value_or(Data{30});
        std::cout << "d: " << d << "\n";
    }

    return 0;
}
