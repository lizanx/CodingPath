#include <iostream>
#include <variant>

int main()
{
    std::variant<int, double, bool> v{2.3};
    try
    {
        std::cout << std::get<int>(v);
    }
    catch (std::bad_variant_access &e)
    {
        std::cout << "Failed to access data in v: " << e.what() << "\n";
    }

    std::cout << "Index of type of currently holden value: " << v.index() << "\n";
    v = 99;
    std::cout << "Index of type of currently holden value: " << v.index() << "\n";
    std::cout << "Holden value: " << std::get<int>(v) << " " << std::get<0>(v) << "\n";

    // Visitor pattern
    struct VariantVisitor
    {
        void operator()(int &value)
        {
            std::cout << "Variant is holding an int: " << value << "\n";
        }
        void operator()(double &value)
        {
            std::cout << "Variant is holding a double: " << value << "\n";
        }
        void operator()(bool &value)
        {
            std::cout << "Variant is holding a bool: " << std::boolalpha << value << "\n";
        }
    };
    v = true;
    std::visit(VariantVisitor{}, v);
    v = 7;
    std::visit(VariantVisitor{}, v);
    v = 8.4;
    std::visit(VariantVisitor{}, v);
}