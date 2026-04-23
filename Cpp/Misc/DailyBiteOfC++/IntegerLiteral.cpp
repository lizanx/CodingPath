#include <cassert>

int main()
{
    int a = 0xf;
    assert(a == 15);

    int b = 0b110;
    assert(b == 6);

    int c = 1'000'000;
    assert(c == 1000000);

    return 0;
}
