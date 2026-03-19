#include <cassert>
#include <chrono>
#include <print>

int main()
{
    namespace sc = std::chrono;
    using namespace std::literals::chrono_literals;

    auto now = sc::system_clock::now();
    assert((500ms + 500ms == 1s));
    assert((std::is_same_v<decltype(now + 1h), sc::system_clock::time_point>));
    assert((std::is_same_v<decltype(sc::system_clock::now() - now), sc::system_clock::duration>));
    assert(5 * 1s == 5s);
    assert(1h * 3 == 3h);
    assert(6s / 2 == 3s);
    assert(7s % 3 == 1s);
    assert(10s / 5000ms == 2);
    assert(1s % 300ms == 100ms);

    return 0;
}
