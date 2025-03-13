#include <functional>
#include <iostream>
#include <string>

class Person
{
public:
    Person(std::string name, int age) : _name{name}, _age{age} {}
    bool IsAdult() const noexcept
    {
        return _age >= 18;
    }

    std::string ResetName(std::string name) noexcept
    {
        std::string prevName{std::move(_name)};
        _name = name;
        return prevName;
    }

    int ResetAge(int age) noexcept
    {
        auto prevAge{_age};
        _age = age;
        return prevAge;
    }

    std::string Name() const noexcept
    {
        return _name;
    }

    int Age() const noexcept
    {
        return _age;
    }

private:
    std::string _name;
    int _age;
};

int main()
{
    Person person{"Johnson", 22};
    Person *p{&person};
    auto personIsAdult = std::mem_fn(&Person::IsAdult);
    std::cout << "Johnson is adult: " << std::boolalpha
              << personIsAdult(person) << "  "
              << personIsAdult(p) << "\n";

    // Bind by value, "person" is copied
    auto valueBindResetName = std::bind(&Person::ResetName, person, std::placeholders::_1);
    valueBindResetName("Kevin");
    std::cout << person.Name() << '\n';

    // Bind by reference, "person" is referenced
    auto refBindResetAge = std::bind(&Person::ResetAge, p, std::placeholders::_1);
    refBindResetAge(33);
    std::cout << p->Age() << '\n';

    // In call to std::bind, arguments are always passed by ref unless explicitly use std::ref/cref
    int n{10};
    auto addFn = [](int a, int b)
    { return a + b; };
    auto boundValueAddFn = std::bind(addFn, n, std::placeholders::_1);
    auto boundRefAddFn = std::bind(addFn, std::ref(n), std::placeholders::_1);
    std::cout << "Bound n by value: add(0) = " << boundValueAddFn(0) << "\n";
    std::cout << "Bound n by ref: add(0) = " << boundRefAddFn(0) << "\n";
    n = 100;
    std::cout << "n set to 100\n";
    std::cout << "Bound n by value: add(0) = " << boundValueAddFn(0) << "\n";
    std::cout << "Bound n by ref: add(0) = " << boundRefAddFn(0) << "\n";

    // After binding, when calling the bound function, arguments are always perfectly forwarded
    auto incFn1 = [](int a)
    { return ++a; };
    auto incFn2 = [](int &a)
    { return ++a; };
    auto boundIncFn1 = std::bind(incFn1, std::placeholders::_1);
    auto boundIncFn2 = std::bind(incFn2, std::placeholders::_1);
    int m = 0;
    n = 0;
    boundIncFn1(m);
    std::cout << "m after boundIncFn1: " << m << '\n';
    boundIncFn2(n);
    std::cout << "n after boundIncFn2: " << n << '\n';
}
