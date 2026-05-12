#include <print>
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

    struct ResourceHandle
    {
        // Used on ctor, warn on temporary object.
        [[nodiscard]] ResourceHandle()
        {
            std::println("Acquiring resource..");
        }
    };

    // Used on type, cannot be discarded when returned by a function
    // even if the function itself is not marked as [[nodiscard]]
    struct [[nodiscard]] Error
    {
        int m_errorCode{};
    };

    Error DoAction()
    {
        return Error{};
    }
}

int main()
{
    MyStruct x{};
    x.ExpensiveCall(); // warning

    CustomVector vec{};
    vec.Empty(); // warning

    auto rh = ResourceHandle{};
    ResourceHandle{}; // warning

    auto err = DoAction();
    DoAction(); // warning

    return 0;
}
