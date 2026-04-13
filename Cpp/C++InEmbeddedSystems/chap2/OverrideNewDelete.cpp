#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <new>
#include <vector>

void *operator new(std::size_t cnt)
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
    std::vector<std::uint8_t> vec{};
    constexpr std::size_t elementCnt = 8;
    // vec.reserve(elementCnt);
    for (std::uint8_t i{}; i < elementCnt; ++i)
    {
        vec.push_back(i);
    }
    const auto printArray = [](uint8_t *arr, std::size_t n)
    {
        for (std::size_t i{}; i < n; ++i)
            printf("%d ", arr[i]);
        printf("\n");
    };
    printArray(vec.data(), vec.size());

    return 0;
}
