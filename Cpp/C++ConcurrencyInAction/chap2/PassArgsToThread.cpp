#include <chrono>
#include <iostream>
#include <thread>

namespace
{
    void PrintIntAndStr1(int n, const std::string &s)
    {
        std::this_thread::sleep_for(std::chrono::seconds{1});
        std::cout << "PrintIntAndStr1 - "
                  << "int: " << n << ", "
                  << "string: " << s << '\n';
    }

    void PrintIntAndStr2(int n, std::string &s)
    {
        std::this_thread::sleep_for(std::chrono::seconds{1});
        std::cout << "PrintIntAndStr2 - "
                  << "int: " << n << ", "
                  << "string: " << s << '\n';
    }

    class Person
    {
    public:
        Person(std::string name, int age) : _name{name}, _age{age}
        {
        }

        void PrintInfo()
        {
            std::cout << "Person: "
                      << "name=" << _name;
            std::this_thread::sleep_for(std::chrono::seconds{1});
            std::cout << ", age=" << _age << '\n';
        }

    private:
        std::string _name;
        int _age;
    };
}

int main(int argc, char *argv[])
{
    std::cout << "================= Thread 1 =================\n";
    std::thread t1{PrintIntAndStr1, 1, "hello"};
    t1.join();

    std::cout << "================= Thread 2 =================\n";
    std::string s{"world"};
    std::thread t2{PrintIntAndStr2, 2, std::ref(s)};
    t2.join();
    // Since "PrintIntAndStr2" requires "std::string&", you must use "std::ref(s)".
    // std::thread t2{PrintIntAndStr2, 2, "world"}; --> compiling error
    // std::thread t2{PrintIntAndStr2, 2, s}; --> compiling error

    std::cout << "================= Thread 3 =================\n";
    Person person{"Gavin", 28};
    // std::thread t3{&Person::PrintInfo}; --> compiling error
    std::thread t3{&Person::PrintInfo, &person}; // Must pass object pointer here, other function arguments following the pointer.
    t3.join();

    std::cout << "Exit main\n";
}
