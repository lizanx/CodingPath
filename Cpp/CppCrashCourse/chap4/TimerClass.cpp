#include <iostream>
#include <chrono>
#include <string>

using namespace std::chrono;
using namespace std::string_literals;

struct TimerClass
{
public:
    TimerClass(const char *name):
        timestamp{ new system_clock::time_point{ system_clock::now() } },
        name{ name }
    {
        std::cout << this->name << "\tNormal Constructor\n";
    }
    TimerClass(const TimerClass& tc):
        timestamp{ new system_clock::time_point{ *tc.timestamp } },
        name{ "CopyCtor["s + tc.name + "]"s }
    {
        std::cout << this->name << "\tCopy Constructor\n";
    }
    TimerClass(TimerClass&& tc) noexcept:
        timestamp{ tc.timestamp },
        name{ "MoveCtor["s + tc.name + "]"s }
    {
        tc.timestamp = nullptr;
        std::cout << this->name << "\tMove Constructor\n";
    }

    ~TimerClass() noexcept
    {
        std::cout << "Destructing " << name << '\n';
        if (timestamp)
        {
            std::cout << "~~~ " << name
                << "\tLive duration: "
                << duration_cast<milliseconds>(system_clock::now() - *timestamp).count()
                << "ms" << std::endl;

            delete timestamp;
        }
    }
    
    TimerClass& operator=(const TimerClass& tc)
    {
        if (this == &tc)
            return *this;
        this->name = "CopyAssign["s + tc.name + "]"s;
        std::cout << this->name << "\tCopy Assignment\n";
        delete timestamp;
        this->timestamp = new system_clock::time_point{ *tc.timestamp };
        return *this;
    }
    TimerClass& operator=(TimerClass&& tc) noexcept
    {
        if (this == &tc)
            return *this;
        this->name = "MoveAssign["s + tc.name + "]"s;
        std::cout << this->name << "\tMove Assignment\n";
        delete this->timestamp;
        this->timestamp = tc.timestamp;
        tc.timestamp = nullptr;
        return *this;
    }

private:
    system_clock::time_point *timestamp;
    std::string name;
};

static void tick(int count = 30000000)
{
    for (int i = 0; i < count; i++)
    {
        if (i % 10000000 == 0)
            std::cout << " ";
    }
    std::cout << "\n";
}

int main(void)
{
    int step = 1;

    std::cout << "----- Step " << step++ << " -----\n";
    TimerClass tc1{ "tc1" };
    tick();

    std::cout << "----- Step " << step++ << " -----\n";
    TimerClass tc2 { tc1 }; // copy construct
    tick();

    std::cout << "----- Step " << step++ << " -----\n";
    tc2 = tc1; // copy assignment
    tick();

    std::cout << "----- Step " << step++ << " -----\n";
    TimerClass tc3 { std::move(tc1) }; // move construct
    tick();

    std::cout << "----- Step " << step++ << " -----\n";
    tc3 = std::move(tc2); // move assignment
    tick();

    return EXIT_SUCCESS;
}
