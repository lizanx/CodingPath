#include <iostream>

class MyClass
{
    int id;

public:
    MyClass(int id) : id{id} {}
    ~MyClass() {}

    int GetId()
    {
        return id;
    }

    int GetNextId()
    {
        // auto getNextId = [id]() { return id + 1; }; // Compile error: id not visible for capture here.
        auto getNextId = [id = id]() // Capture by value. By reference: [&id = id]
        { return id + 1; };
        return getNextId();
    }
};

int main()
{
    MyClass myClassObj(10);
    std::cout << "Id of my-class-obj: " << myClassObj.GetId() << "\n";
    std::cout << "Id of next object: " << myClassObj.GetNextId() << "\n";

    return EXIT_SUCCESS;
}
