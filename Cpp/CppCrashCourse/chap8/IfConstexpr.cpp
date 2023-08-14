#include <iostream>
#include <type_traits>

template<typename T>
auto value_of(T x)
{
    if constexpr (std::is_pointer<T>::value)
    {
        if (x == nullptr) throw std::runtime_error("Null pointer dereference.");
        return *x;
    }
    else
    {
        return x;
    }
}

int main()
{
    unsigned cnt{5};
    auto cnt_ptr = &cnt;
    auto &cnt_ref = cnt;
    std::cout << "Value of cnt: " << value_of(cnt++) << '\n';
    std::cout << "Value of cnt_ptr: " << value_of(cnt_ptr) << '\n';
    std::cout << "Value of cnt_ref: " << value_of(++cnt_ref) << '\n';
}