#include <cassert>
#include <memory>
#include <print>
#include <vector>
#include <string>

namespace
{
    void Demo_CopyMoveFill()
    {
        std::vector<std::string> src{"Hello", "World"};

        void *buffer = std::aligned_alloc(alignof(std::string), sizeof(std::string) * src.size());
        if (!buffer)
            throw std::runtime_error{"Failed to alloc"};

        auto rawIter = static_cast<std::string *>(buffer);
        {
            // Copy construction
            auto endIter = std::uninitialized_copy(src.begin(), src.end(), rawIter);
            assert((endIter - rawIter == src.size()));

            std::print("Strings after uninitialized_copy: ");
            for (auto iter = rawIter; iter != endIter; ++iter)
                std::print("{} ", *iter);
            std::println();

            // Manual creation requires manual destruction
            std::destroy(rawIter, endIter); // call dtors
        }
        {
            auto endIter = rawIter + src.size();
            // Copy construction from a single value
            std::uninitialized_fill(rawIter, endIter, std::string{"hello"});

            std::print("Strings after uninitialized_fill: ");
            for (auto iter = rawIter; iter != endIter; ++iter)
                std::print("{} ", *iter);
            std::println();

            // Manual creation requires manual destruction
            std::destroy(rawIter, endIter);
        }
        {
            // Move construction
            auto endIter = std::uninitialized_move(src.begin(), src.end(), rawIter);
            assert((endIter - rawIter == src.size()));

            std::print("Strings after uninitialized_move: ");
            for (auto iter = rawIter; iter != endIter; ++iter)
                std::print("{} ", *iter);
            std::println();

            // Manual creation requires manual destruction
            std::destroy(rawIter, endIter);
        }

        std::free(buffer);
    }

    void Demo_ValueDefault()
    {
        constexpr size_t size = 7;
        void *buffer = std::aligned_alloc(alignof(int), sizeof(int) * size);
        if (!buffer)
            throw std::runtime_error{"Failed to alloc"};

        auto rawIter = static_cast<int *>(buffer);
        auto endIter = rawIter + size;

        // Value construction:
        // - for POD it means zero-initialization
        // - for non-POD it means default construction
        std::uninitialized_value_construct(rawIter, endIter);
        assert(std::all_of(rawIter, endIter, [](int n)
                           { return n == 0; }));

        // Manual creation requires manual destruction.
        std::destroy(rawIter, endIter);

        // Default construction:
        // - for POD it means uninitialized non-determinate values(random garbage in memory)
        // - for non-POD it means default construction
        std::uninitialized_default_construct(rawIter, endIter);
        std::destroy(rawIter, endIter);

        std::free(buffer);
    }
}

int main()
{
    Demo_CopyMoveFill();

    Demo_ValueDefault();

    return 0;
}
