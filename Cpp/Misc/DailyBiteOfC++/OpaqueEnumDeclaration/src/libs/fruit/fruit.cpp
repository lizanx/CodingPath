#include "fruit.hpp"
#include <print>

enum class Fruit : uint32_t
{
    Apple,
    Banana,
    Grape,
    Pear,
    Peach,
};

Fruit GetApple()
{
    return Fruit::Apple;
}

Fruit GetBanana()
{
    return Fruit::Banana;
}

void Display(Fruit fruit)
{
    switch (fruit)
    {
    case Fruit::Apple:
        std::println("The fruit type is Fruit::Apple");
        break;
    case Fruit::Banana:
        std::println("The fruit type is Fruit::Banana");
        break;
    case Fruit::Grape:
        std::println("The fruit type is Fruit::Grape");
        break;
    case Fruit::Pear:
        std::println("The fruit type is Fruit::Pear");
        break;
    case Fruit::Peach:
        std::println("TPeache");
        break;
    default:
        break;
    }
}
