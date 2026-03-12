#include <print>
#include <ranges>
#include <utility>
#include <vector>

int main()
{
    std::vector<int> data{1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (const auto [index, chunk] : data | std::views::chunk(4) | std::views::enumerate)
    {
        std::print("Chunk[{}]: ", index);
        for (const int n : chunk)
            std::print("{} ", n);
        std::println();
    }
    std::println("\n\n");

    {
        auto view = data | std::views::chunk(4);

        auto secondChunk = view[1];
        std::print("Second chunk: ");
        for (int n : secondChunk)
            std::print("{} ", n);
        std::println();

        auto lastChunk = view.back();
        std::print("Last chunk: ");
        for (int n : lastChunk)
            std::print("{} ", n);
        std::println();
    }
    std::println("\n\n");

    {
        auto cube = std::views::iota(0, 27) | std::ranges::to<std::vector<int>>();
        for (const auto [index, slice] : cube | std::views::chunk(3 * 3) | std::views::enumerate)
        {
            std::println("Slice[{}]", index);
            for (const auto [rowIndex, row] : slice | std::views::chunk(3) | std::views::enumerate)
            {
                std::print("\tRow[{}]: ", rowIndex);
                for (int n : row)
                    std::print("{} ", n);
                std::println();
            }
        }
    }

    return 0;
}
