#include <atomic>
#include <print>

namespace
{
    struct A
    {
        int a[8]{};
    };

    struct B
    {
        int x{};
        int y{};
    };

}

int main(int argc, char *argv[])
{
    std::atomic<bool> varBool{};
    std::println("Is atomic<bool> lock free? \t\t{}(Always) {}/{}(runtime)",
                 std::atomic<bool>::is_always_lock_free, std::atomic_is_lock_free(&varBool), varBool.is_lock_free());
    std::println("Is atomic<int> lock free? \t\t{}(Always) {}(runtime)",
                 std::atomic<int>::is_always_lock_free, std::atomic<int>{}.is_lock_free());
    std::println("Is atomic<char> lock free? \t\t{}(Always) {}(runtime)",
                 std::atomic<char>::is_always_lock_free, std::atomic<char>{}.is_lock_free());
    std::println("Is atomic<unsigned> lock free? \t\t{}(Always) {}(runtime)",
                 std::atomic<unsigned>::is_always_lock_free, std::atomic<unsigned>{}.is_lock_free());
    std::println("Is atomic<long> lock free? \t\t{}(Always) {}(runtime)",
                 std::atomic<long>::is_always_lock_free, std::atomic<long>{}.is_lock_free());
    std::println("Is atomic<long long> lock free? \t\t{}(Always) {}(runtime)",
                 std::atomic<long long>::is_always_lock_free, std::atomic<long long>{}.is_lock_free());
    std::println("Is atomic<float> lock free? \t\t{}(Always) {}(runtime)",
                 std::atomic<float>::is_always_lock_free, std::atomic<float>{}.is_lock_free());
    std::println("Is atomic<double> lock free? \t\t{}(Always) {}(runtime)",
                 std::atomic<double>::is_always_lock_free, std::atomic<double>{}.is_lock_free());
    std::println("Is atomic<std::uintptr_t> lock free? \t\t{}(Always) {}(runtime)",
                 std::atomic<std::uintptr_t>::is_always_lock_free, std::atomic<std::uintptr_t>{}.is_lock_free());
    std::println("Is atomic<void*> lock free? \t\t{}(Always) {}(runtime)",
                 std::atomic<void *>::is_always_lock_free, std::atomic<void *>{}.is_lock_free());
    // std::atomic<A>{}.is_lock_free() fails to compile.
    std::println("Is atomic<A> lock free? \t\t{}(Always)",
                 std::atomic<A>::is_always_lock_free);
    std::println("Is atomic<B> lock free? \t\t{}(Always) {}(runtime)",
                 std::atomic<B>::is_always_lock_free, std::atomic<B>{}.is_lock_free());
}
