#include <array>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <memory_resource>
#include <new>
#include <vector>

void *operator new(std::size_t cnt)
{
    printf("%s: size = %zu\n", __PRETTY_FUNCTION__, cnt);
    return std::malloc(cnt);
}

// Will be called!!!
void *operator new(std::size_t cnt, std::align_val_t align)
{
    printf("%s: size = %zu\n", __PRETTY_FUNCTION__, cnt);
    return std::malloc(cnt);
}

void operator delete(void *ptr) noexcept
{
    printf("%s\n", __PRETTY_FUNCTION__);
    std::free(ptr);
}

int main()
{
    std::array<uint8_t, sizeof(uint8_t) * 8> buffer{0};
    std::pmr::monotonic_buffer_resource mbr{buffer.data(), buffer.size()};
    std::pmr::polymorphic_allocator<uint8_t> polyAlloc{&mbr};
    std::pmr::vector<uint8_t> vec{polyAlloc};

    constexpr std::size_t elementCnt = 8;
    // vec.reserve(elementCnt);
    for (std::uint8_t i{}; i < elementCnt; ++i)
    {
        vec.push_back(i);
    }

    // The "double the capacity" strategy will grow the size of the vector beyond
    // the memory buffer resource, since it always allocates new memory at next
    // available address before freeing the previously allocated memory.
    for (uint8_t data : buffer)
        printf("%u ", data); // 0 0 1 0 1 2 3 0
    printf("\n");

    return 0;
}
