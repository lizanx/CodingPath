#include "String.hpp"

int main(int argc, char *argv[])
{
    using self_def_str::String;

    String s1{};
    String s2{"Hello World"};
    String s3{s2};
    String s4 = s2 + s3;

    std::cout << "s1: " << s1.size() << " - " << s1 << "\n"
              << "s2: " << s2.size() << " - " << s2 << "\n"
              << "s3: " << s3.size() << " - " << s3 << "\n"
              << "s4: " << s4.size() << " - " << s4 << "\n";

    String s5{"Complex C++"};
    s5 += " | ";
    s5 += s2;
    std::cout << "s5: " << s5.size() << " - " << s5 << "\n";

    const String s6{s5};
    for (size_t i{}; i < s6.size(); ++i)
        std::cout << s6[i] << ' ';
    std::cout << '\n';
}
