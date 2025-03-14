#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

namespace
{
    void CheckWeakPointer(int id, std::weak_ptr<int> p, std::chrono::seconds sleepDuration)
    {
        auto printIdPrefix = [id]()
        {
            std::cout << "Thread[" << id << "] ";
        };

        printIdPrefix();
        std::cout << "Ptr expired = " << p.expired()
                  << ", use count = " << p.use_count()
                  << "\n";

        std::this_thread::sleep_for(sleepDuration);

        printIdPrefix();
        std::cout << "After sleep, "
                  << "Ptr expired = " << p.expired()
                  << ", use count = " << p.use_count()
                  << "\n";
    }
}

int main()
{
    std::cout << std::boolalpha;

    auto shortLivedInt = std::make_shared<int>(1);
    auto longLivedInt = std::make_shared<int>(2);

    std::jthread t1{CheckWeakPointer, *shortLivedInt, std::weak_ptr<int>{shortLivedInt}, std::chrono::seconds{5}};
    std::this_thread::sleep_for(std::chrono::seconds{1});
    std::jthread t2{CheckWeakPointer, *longLivedInt, std::weak_ptr<int>{longLivedInt}, std::chrono::seconds{5}};

    std::this_thread::sleep_for(std::chrono::seconds{3});
    shortLivedInt.reset();

    std::this_thread::sleep_for(std::chrono::seconds{3});
    longLivedInt.reset();
}
