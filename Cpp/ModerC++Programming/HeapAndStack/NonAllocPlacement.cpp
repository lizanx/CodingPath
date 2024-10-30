#include <iostream>

class MyClass
{
public:
    int id;

    MyClass(int id) : id{id}
    {
    }

    ~MyClass()
    {
        std::cout << "Destructing MyClass-" << id << "\n";
    }
};

int main()
{
    std::cout << "### Non-Allocating Placement ###\n";
    char buffer[32];
    int *i = new (buffer) int(16);
    int *j = new (buffer + 16) int(1024);
    std::cout << "Address of buffer: " << std::showbase << std::hex << &(buffer[0]) << "\n";
    std::cout << "Value of buffer: " << std::dec << *((int *)buffer) << "\n";
    std::cout << "Address of i: " << std::showbase << std::hex << i << "\n";
    std::cout << "Value of i: " << std::dec << *i << "\n";
    std::cout << "Address of buffer + 16: " << std::showbase << std::hex << &(buffer[16]) << "\n";
    std::cout << "Value of buffer + 16: " << std::dec << *((int *)(buffer + 16)) << "\n";
    std::cout << "Address of j: " << std::showbase << std::hex << j << "\n";
    std::cout << "Value of j: " << std::dec << *j << "\n";
    // delete i; // i is not trully dynamically allocated, this causes runtime abortion.
    // delete j; // j is not trully dynamically allocated, this causes runtime abortion.

    std::cout << "\n\n### Non-Allocating Placement for non-trivial objects ###\n";
    char buf[sizeof(MyClass)];
    MyClass *myClassObj = new (buf) MyClass(1);
    std::cout << "Address of buf: " << std::showbase << std::hex << buf << "\n";
    std::cout << "Address of myClassObj: " << std::showbase << std::hex << myClassObj << "\n";
    std::cout << "Id of myClassObj: " << myClassObj->id << "\n";
    // delete myClassObj; // myClassObj is not trully allocated on heap, this will cause runtime abortion.
    myClassObj->~MyClass(); // Since you can't delete the non-heap pointer, you must explicitly call destructor.

    return EXIT_SUCCESS;
}
