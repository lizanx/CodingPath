#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>

int main(int argc, char *argv[])
{
    std::ifstream inFile{"input.txt"};
    if (!inFile)
        throw std::runtime_error{"Failed to open input."};

    std::istream_iterator<std::string> inIter{inFile}, inEndIter{};
    std::ostream_iterator<std::string> outIter{std::cout, "\n"};
    std::vector vec(inIter, inEndIter);
    std::sort(std::begin(vec), std::end(vec));
    std::unique_copy(std::begin(vec), std::end(vec), outIter);
}
