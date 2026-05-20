#include <cassert>
#include <filesystem>
#include <print>

int main()
{
    std::filesystem::path local{"."};
    for (const auto &entry : std::filesystem::directory_iterator(local))
    {
        auto p1 = entry.path();            // ./<file>
        auto p2 = absolute(entry.path());  // /xxx/./<file>
        auto p3 = canonical(entry.path()); // /xxx/<file>
        assert(equivalent(p1, p2));
        assert(equivalent(p2, p3));

        if (entry.path().filename().string().starts_with("A"))
            std::println("File: {}\t{}\t{}", p1.c_str(), p2.c_str(), p3.c_str());
    }

    for (const auto &entry : std::filesystem::recursive_directory_iterator(std::filesystem::path{"../.."}))
    {
        auto p1 = entry.path();            // ./<file>
        auto p2 = absolute(entry.path());  // /xxx/./<file>
        auto p3 = canonical(entry.path()); // /xxx/<file>
        assert(equivalent(p1, p2));
        assert(equivalent(p2, p3));

        if (entry.path().filename().string().starts_with("B"))
            std::println("File: {}\t{}\t{}", p1.c_str(), p2.c_str(), p3.c_str());
    }

    return 0;
}
