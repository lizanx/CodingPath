#include <iostream>

template <int... NArgs>
struct Add;

template <int N1, int N2>
struct Add<N1, N2>
{
    static constexpr int value = N1 + N2;
};

template <int N, int... NArgs>
struct Add<N, NArgs...>
{
    static constexpr int value = N + Add<NArgs...>::value;
};

int main()
{
    std::cout << Add<1, 2, 3>::value << "\n"
              << Add<4, 5>::value << "\n";

    return EXIT_SUCCESS;
}
