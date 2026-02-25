#include <algorithm>
#include <barrier>
#include <print>
#include <random>
#include <thread>
#include <vector>

namespace
{
    constexpr int RUNNER_COUNT = 6;

    void Test1()
    {
        std::barrier phase(RUNNER_COUNT, [id = 1] mutable
                           {
        std::println("Phase {} complete.", id);
        ++id; });
        std::vector<std::jthread> runners{};
        std::generate_n(std::back_inserter(runners), RUNNER_COUNT, [&phase]
                        { return std::jthread{[&phase]
                                              {
                                                  std::println("Running phase 1 for thread {}", std::this_thread::get_id());
                                                  std::this_thread::yield();

                                                  phase.arrive_and_wait();

                                                  std::println("Running phase 2 for thread {}", std::this_thread::get_id());
                                                  std::this_thread::yield();

                                                  phase.arrive_and_wait();
                                              }}; });
        runners.clear();
    }

    void Test2()
    {
        std::barrier barrier(RUNNER_COUNT);
        std::vector<std::jthread> runners{};
        std::generate_n(std::back_inserter(runners), RUNNER_COUNT, [&barrier]
                        { return std::jthread{[&barrier]
                                              {
                                                  auto seed = std::hash<std::thread::id>{}(std::this_thread::get_id());
                                                  std::mt19937 gen{seed};
                                                  std::bernoulli_distribution done{0.3}; // 30% for true, 70% for false.

                                                  int id = 1;
                                                  for (;;)
                                                  {
                                                      std::println("Running phase {} for thread {}", id, std::this_thread::get_id());
                                                      std::this_thread::yield();
                                                      if (done(gen))
                                                      {
                                                          barrier.arrive_and_drop();
                                                          return;
                                                      }
                                                      barrier.arrive_and_wait();
                                                      ++id;
                                                  }
                                              }}; });
    }
}

int main()
{
    Test1();
    std::println("\n================================\n");
    Test2();
}
