#include <string>

struct Person
{
    Person() : Name{ "Anonymous" }, Age{ 0 } {}
    Person(const char *name, int age) : Name{ name }, Age{ age } {}

    std::string Name;
    int Age;
};
