#include <utility>

namespace
{
    struct Empty
    {
    };

    struct Bigger
    {
        int value;
        Empty empty;
    };

    struct SameAsInt
    {
        int value;
        [[no_unique_address]] Empty empty;
    };
}

int main()
{
    static_assert(sizeof(Empty) >= 1);
    static_assert(sizeof(Bigger) >= sizeof(int) + 1);
    static_assert(sizeof(SameAsInt) == sizeof(int));
}
