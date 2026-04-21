#include <atomic>
#include <print>
#include <stdexcept>

namespace
{
    std::atomic<int> g_id{};

    struct Obj
    {
    public:
        Obj()
        {
            std::println("Obj[{}] constructed.", m_id);
        }

        ~Obj()
        {
            std::println("Obj[{}] destructed.", m_id);
        }

    private:
        int m_id{++g_id};
    };

}

int main()
{
    std::println("===== Non-trivially destructible =====");
    {
        Obj *pObj = new Obj[5]; // construction: 1~5
        if (!pObj)
            throw std::runtime_error{"Failed to alloc objects"};
        int64_t *cookie = std::bit_cast<int64_t *>(std::bit_cast<uintptr_t>(pObj) - 8);
        std::println("Cookie: {}", *cookie); // Cookie should be 5 (Linux + glibc)
        delete[] pObj;                       // destruction: 5~1
    }

    std::println("===== Trivially destructible =====");
    {
        int *pInt = new int[5];
        if (!pInt)
            throw std::runtime_error{"Failed to alloc ints"};
        int64_t *cookie = std::bit_cast<int64_t *>(std::bit_cast<uintptr_t>(pInt) - 8);
        std::println("Cookie: {}", *cookie); // undefined behavior, cookie is optimized away for trivially destructible types.
        delete[] pInt;
    }

    return 0;
}
