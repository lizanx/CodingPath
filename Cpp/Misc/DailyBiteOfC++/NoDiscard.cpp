#include <thread>

namespace
{
    struct MyStruct
    {
        [[nodiscard]] int ExpensiveCall()
        {
            std::this_thread::sleep_for(std::chrono::seconds{2});
            return 1;
        }
    };

    struct CustomVector
    {
        [[nodiscard("Do you mean to call clear()?")]]
        bool Empty() const
        {
            return false;
        }
    };
}

int main()
{
    MyStruct x{};
    x.ExpensiveCall(); // warning

    CustomVector vec{};
    vec.Empty(); // warning

    return 0;
}
