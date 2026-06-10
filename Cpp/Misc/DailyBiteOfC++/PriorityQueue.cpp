#include <queue>
#include <iostream>
#include <iomanip>

namespace
{
    void DemoDefaultImpl()
    {
        std::cout << "=== DemoDefaultImpl ===\n";

        std::priority_queue<int> q{};
        q.push(1);
        q.push(2);
        q.push(3);
        q.push(4);

        while (!q.empty())
        {
            std::cout << "Value: " << q.top() << '\n';
            q.pop();
        }

        std::cout << "--- DemoDefaultImpl ---\n";
    }

    void DemoCustomImpl()
    {
        std::cout << "=== DemoCustomImpl ===\n";

        auto comparator = [](const std::string &left, const std::string &right)
        {
            return left.length() > right.length();
        };

        std::priority_queue<std::string, std::vector<std::string>, decltype(comparator)> q{};
        q.push("a");
        q.push("bb");
        q.push("ccc");
        q.push("dddd");

        while (!q.empty())
        {
            std::cout << "Value: " << q.top() << '\n';
            q.pop();
        }

        std::cout << "--- DemoCustomImpl ---\n";
    }
}

int main()
{
    DemoDefaultImpl();

    DemoCustomImpl();

    return 0;
}
