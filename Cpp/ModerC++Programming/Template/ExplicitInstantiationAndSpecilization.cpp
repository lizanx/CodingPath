#include <iostream>

template <typename T>
constexpr T PI{3.14159265};

template <typename T>
struct Rectangle
{
    T Width;
    T Height;
};

template <typename T>
T CalculateArea(const Rectangle<T> &rect)
{
    std::cout << "Calling CalculateArea for Rectangle<" << typeid(T).name() << ">\n";
    return rect.Height * rect.Width;
}

// Explicit template instantiation
template int CalculateArea(const Rectangle<int> &rect);

// Template specialization
template <>
double CalculateArea(const Rectangle<double> &rect)
{
    std::cout << "Calling double-specialized CalculateArea for Rectangle<"
              << typeid(double).name() << ">\n";
    return rect.Height * rect.Width;
}

int main()
{
    Rectangle<int> intRect{3, 4};
    std::cout << CalculateArea<int>(intRect) << "\n\n";

    Rectangle<double> doubleRect{3.3, 4.4};
    std::cout << CalculateArea<double>(doubleRect) << "\n\n";

    return EXIT_SUCCESS;
}
