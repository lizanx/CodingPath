#include <bitset>
#include <cassert>

int main()
{
    std::bitset<16> data{};

    data[0] = 1; // LSB
    assert(data.to_ulong() == 1);

    data.set();
    assert(data.to_ulong() == 65535);

    data.flip();
    assert(data.to_ulong() == 0);

    data[0] = 1;
    data[2] = 1;
    data[4] = 1;

    std::bitset<16> other{};
    other[0] = 1;
    other[2] = 1;

    auto result = data & other;
    assert(result.to_ulong() == 5);
    assert(result.any());
    assert(result.count() == 2);
    assert(result == other);

    return 0;
}
