#include <iostream>
#include <string>
#include <utility>

template <typename TFunc, typename... TArgs>
void call(TFunc &&func, TArgs &&...args)
{
    func(std::forward<TArgs>(args)...);
}

void f0()
{
    std::cout << "f0()\n";
}

template <typename T>
void f1(T arg)
{
    std::cout << "f1(" << arg << ")\n";
}

void f1int(int i)
{
    std::cout << "f1int(" << i << ")\n";
}

template <typename T1, typename T2>
void f2(T1 arg1, T2 arg2)
{
    std::cout << "f2(" << arg1 << ", " << arg2 << ")\n";
}

int main(int argc, char *argv[])
{
    call(f0);
    call(f1<double>, 3.14);
    // call(f1<double>, 3.14, 5); // error: too many arguments to function call, expected 1, have 2
    call(f1int, 2);
    call(f2<std::string, char>, std::string{"Hello"}, 'W');
    // call(f2<std::string, char>, std::string{"Word"}); // error: too few arguments to function call, expected 2, have 1

    int i{100};
    double d{5.99};
    std::string s{"C++"};
    call(f1<double>, d);
    call(f1int, i);
    call(f2<std::string, double>, s, d);
}
