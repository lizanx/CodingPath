#include <cassert>
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

    std::string Stringify(const Data &data)
    {
        return std::to_string(data.m_value);
    }

    int Integerify(const std::string &str)
    {
        return std::stoi(str);
    }

    std::optional<Data> FetchFromDb()
    {
        return Data{42};
    }

    void TestMonadicOpes()
    {
        std::optional<Data> data{};

        auto r1 = data.transform(Stringify).transform(Integerify);
        assert(r1 == std::nullopt);

        data = Data{22};
        auto r2 = data.transform(Stringify).transform(Integerify);
        assert((r2.has_value() && r2.value() == 22));

        auto r3 = data.and_then([](const Data &d)
                                {
            if (d.m_value % 2 == 0)
                return std::optional<std::string>{"Even"};
            return std::optional<std::string>{"Odd"}; });
        assert((r3.has_value() && r3.value() == "Even"));

        data = std::nullopt;
        auto r4 = data.or_else(FetchFromDb);
        assert((r4.has_value() && r4.value().m_value == 42));

        auto r5 = FetchFromDb().or_else([]()
                                        { return std::optional<Data>{{33}}; })
                      .transform([](const Data &data) -> double
                                 { return data.m_value; })
                      .and_then([](double d)
                                {
                                        if (d > 0.0)
                                            return std::optional<std::string>{"Positive"};
                                        return std::optional<std::string>{"Non-positive"}; });
        assert((r5.has_value() && r5.value() == "Positive"));
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

    TestMonadicOpes();

    return 0;
}
