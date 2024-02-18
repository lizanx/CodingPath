#include <iostream>
#include <set>
#include <cstring>

using namespace std;

int main(int argc, char *argv[])
{
    auto cmp = [](const char *x, const char* y)
        {
            return strcmp(x, y) < 0 ? true : false;
        };
    
    set<const char*, decltype(cmp)> s(cmp);

    for (int i{}; i < argc; i++)
    {
        s.insert(argv[i]);
        cout << "Original argument " << i << ": " << argv[i] << endl;
    }

    for (const auto& e : s)
    {
        cout << "Set element: " << e << endl;
    }
}