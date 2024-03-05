#include <iostream>
#include <thread>
#include <chrono>

int main(void)
{
    using namespace std::literals::chrono_literals;

    std::cout << "Sleep for 3 seconds...\n";
    std::this_thread::sleep_for(3s);

    std::cout << "Thread id: " << std::this_thread::get_id() << "\n";

    std::cout << "Yielding...\n";
    std::this_thread::yield();

    std::cout << "Done." << std::endl;
}
