#include <cassert>
#include <memory>

namespace
{
    struct Demo
    {
        // The '&' operator can be overloaded.
        Demo *operator&()
        {
            return nullptr;
        }
    };
}

int main()
{
    Demo d{};
    assert(&d == nullptr);
    assert(std::addressof(d) != nullptr); // std::addressof to rescue

    return 0;
}
