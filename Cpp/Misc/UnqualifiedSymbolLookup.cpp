#include <iostream>

namespace
{
int x{1};
}

namespace n
{
int x{2};
int y{3};
} // namespace n

namespace a
{
namespace b
{
int g()
{
    using namespace n;
    return y;
}

int h()
{
    // The priority of symbol resolution scope "using namespace XXX" is the same
    // of the global scope.
    // Therefore, this using statement will cause ambiguity between ::x and n::x.
    // using namespace n;

    return x;
}
} // namespace b
} // namespace a

int main(int argc, char *argv[])
{
    std::cout << "g(): " << a::b::g() << "\n"
              << "h(): " << a::b::h() << "\n";
}
