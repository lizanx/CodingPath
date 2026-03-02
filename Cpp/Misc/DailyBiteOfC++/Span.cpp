#include <cstdint>
#include <cstring>
#include <print>
#include <span>
#include <vector>
#include <ranges>

namespace
{
    // C-style api
    size_t Read(char *buffer, size_t size)
    {
        for (size_t i{}; i < size; ++i)
        {
            std::println("Buf[{}] = {}", i, buffer[i]);
        }

        return size;
    }

    // C-style api
    int GetData(char **buffer, size_t *size)
    {
        if (!buffer || !size)
            return -1;

        *buffer = static_cast<char *>(malloc(sizeof(char) * 6));
        if (!*buffer)
            return -2;

        *size = sizeof(char) * 6;
        strcpy(*buffer, "hello");

        return 0;
    }
}

int main()
{
    char buffer[16] = "Hello, world!";
    auto view = std::span{buffer};
    Read(view.data(), view.size());
    for (auto e : view.subspan(0, 5))
        std::print("{}", e);
    std::println("\n");

    char *buf;
    size_t length;
    if (GetData(&buf, &length))
    {
        std::println("Failed to get data.");
        exit(-1);
    }
    auto bufView = std::span{buf, length};
    for (auto iter = bufView.rbegin(); iter != bufView.rend(); ++iter)
        std::print("{}", *iter);
    std::println("\n");
    for (auto e : bufView | std::views::drop(2))
        std::print("{}", e);
    std::println("\n");

    struct Data
    {
        int x;
        int y;
    };
    std::vector<Data> data{
        {2, 3},
        {1, 5},
        {4, 4}};
    std::span<std::byte> bytes = std::as_writable_bytes(std::span{data});
    std::println("Length of bytes: {}", bytes.size());
    std::println();

    auto dynamicSpan = std::span(data);
    // constexpr size_t dynamicSize = dynamicSpan.size();
    auto staticSpan = std::span<Data, 3>{data};
    constexpr size_t staticSize = staticSpan.size();
    std::println("Size of dynamic span: {}", sizeof(dynamicSpan));
    std::println("Size of static span: {}", sizeof(staticSpan));

    return 0;
}
