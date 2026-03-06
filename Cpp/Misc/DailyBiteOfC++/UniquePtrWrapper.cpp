#include <cstdio>
#include <memory>
#include <print>

namespace
{
    template <typename T, typename D>
    auto WrapUnique(T *ptr, D &&deleter)
    {
        return std::unique_ptr<T, D>{ptr, std::forward<D>(deleter)};
    }
}

int main()
{
    auto fp = WrapUnique(fopen("UniquePtrWrapper.cpp", "r"), [](FILE *f)
                         { std::println("Closing.."); fclose(f); });
    char *buf = static_cast<char *>(malloc(1024));
    if (!buf)
    {
        std::println("Failed to malloc");
        exit(-1);
    }
    size_t bufSize{1024};
    auto readCnt = getline(&buf, &bufSize, fp.get());
    if (readCnt < 0)
    {
        std::println(stderr, "Failed to read, ret = {}", readCnt);
        exit(-1);
    }
    std::println("First line: {}", buf);
    free(buf);

    return 0;
}
