#include <iostream>
#include <vector>

using namespace std;

static int fibonacci(size_t index)
{
    static vector<int> buf{1, 2};

    if (index < buf.size())
    {
        return buf[index];
    }

    while (index >= buf.size())
    {
        buf.push_back(buf[buf.size() - 2] + buf.back());
    }
    
    return buf[index];
}

int main(void)
{
    vector<unsigned long> vec{};
    cout << "Capacity: " << vec.capacity() << endl;
    
    vec.reserve(10);
    for (size_t i{0}; i < 20; i++)
    {
        vec.push_back(fibonacci(i));
    }
    cout << "Capacity: " << vec.capacity() << endl;
    for (const auto& e : vec)
    {
        cout << e << ", ";
    }
    cout << endl;
}