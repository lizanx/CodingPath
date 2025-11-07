#include <atomic>
#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <syncstream>
#include <thread>

namespace
{
    template <typename T>
    class LockFreeStack
    {
    public:
        ~LockFreeStack()
        {
            while (Pop())
            {
            }
        }

        void Push(const T &data)
        {
            std::shared_ptr<Node> newNode = std::make_shared<Node>(data);
            newNode->Next = std::atomic_load(&_head);
            while (!std::atomic_compare_exchange_weak(&_head, &newNode->Next, newNode))
            {
            }
        }

        std::shared_ptr<T> Pop()
        {
            std::shared_ptr<Node> oldHead = std::atomic_load(&_head);
            while (oldHead && !std::atomic_compare_exchange_weak(&_head, &oldHead, std::atomic_load(&oldHead->Next)))
            {
            }
            if (oldHead)
            {
                std::atomic_store(&oldHead->Next, std::shared_ptr<Node>{});
                return oldHead->Data;
            }
            return std::shared_ptr<T>{};
        }

    private:
        class Node
        {
        public:
            std::shared_ptr<T> Data;
            std::shared_ptr<Node> Next{};
            Node(const T &data) : Data{std::make_shared<T>(data)}
            {
            }
        };

        std::shared_ptr<Node> _head{};
    };

    int RandInt(int low, int high)
    {
        static std::random_device rd{};
        static std::mt19937 generator{};
        std::uniform_int_distribution distribution{low, high};
        return distribution(generator);
    }
}

int main(int argc, char *argv[])
{
    std::osyncstream oss{std::cout};
    LockFreeStack<int> stack{};
    auto threadFn = [&oss, &stack]()
    {
        int cnt{};
        while (++cnt <= 20)
        {
            int operation = RandInt(0, 1);
            if (operation == 0) // Push
            {
                int data = RandInt(0, 9);
                stack.Push(data);
                oss << "++ Push " << data << "\n";
            }
            else // Pop
            {
                auto data = stack.Pop();
                if (data)
                    oss << "-- Pop " << *data << "\n";
                else
                    oss << "-- Pop none, empty.\n";
            }

            std::this_thread::sleep_for(std::chrono::milliseconds{2});
        }
    };
    {
        std::jthread t1{threadFn};
        std::jthread t2{threadFn};
        std::jthread t3{threadFn};
        std::jthread t4{threadFn};
    }

    oss << "## Exit main.\n";
    return 0;
}
