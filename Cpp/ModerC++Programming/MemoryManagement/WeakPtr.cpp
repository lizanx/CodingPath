#include <iostream>
#include <memory>

int main()
{
    std::weak_ptr<int> wp1{};
    std::cout << std::boolalpha << wp1.use_count() << " " << wp1.expired() << "\n";

    int *ptr = new int;
    // std::weak_ptr<int> wp2(new int); // Compiler error
    // std::weak_ptr<int> wp2(ptr); // Compiler error
    delete ptr;

    auto sp = std::make_shared<int>(10);
    std::weak_ptr<int> wp3(sp);
    std::cout << sp.use_count() << " " << wp3.use_count()
              << " " << wp3.expired() << "\n";
    std::shared_ptr<int> sp2 = sp;
    std::cout << sp.use_count() << " " << wp3.use_count()
              << " " << wp3.expired() << "\n";
    sp = nullptr;
    std::cout << sp2.use_count() << " " << wp3.use_count()
              << " " << wp3.expired() << "\n";
    if (auto sp3 = wp3.lock())
    {
        std::cout << sp3.use_count() << " " << wp3.use_count()
                  << " " << wp3.expired() << "\n";
    }
    sp2 = nullptr;
    std::cout << sp2.use_count() << " " << wp3.use_count()
              << " " << wp3.expired() << "\n";
}
