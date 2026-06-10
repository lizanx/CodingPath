#include <cassert>
#include <string>
#include <vector>

int main()
{
    std::vector<int> data1{1, 3, 4, 5};
    std::vector<int> data2{1, 3, 6, 7};
    std::vector<int> data3{1, 3};

    assert(data1 < data2);
    assert(data3 < data2);

    std::u8string str1 = u8"😀😄😁";
    std::u8string str2 = u8"😁😁😁";
    std::u8string str3 = u8"😁";

    assert(str1 < str2);
    assert(str3 < str2);

    return 0;
}
