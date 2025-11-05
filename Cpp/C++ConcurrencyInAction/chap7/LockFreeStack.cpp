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
        void Push(const T &data)
        {
            Node *newNode = new Node{data};
            newNode->Next = _head.load();
            while (!_head.compare_exchange_weak(newNode->Next, newNode))
            {
            }
        }

        std::shared_ptr<T> Pop()
        {
            ++_threadsInPop;
            Node *oldHead = _head.load();
            while (oldHead && !_head.compare_exchange_weak(oldHead, oldHead->Next))
            {
            }
            std::shared_ptr<T> result{};
            if (oldHead)
                result.swap(oldHead->Data);
            TryReclaim(oldHead);
            return result;
        }

    private:
        class Node
        {
        public:
            std::shared_ptr<T> Data;
            Node *Next{};
            Node(const T &data) : Data{std::make_shared<T>(data)}
            {
            }
        };

        std::atomic<Node *> _head{};
        std::atomic<unsigned> _threadsInPop{};
        std::atomic<Node *> _toBeDeleted{};

        void TryReclaim(Node *oldHead)
        {
            if (_threadsInPop == 1)
            {
                Node *nodesToDelete = _toBeDeleted.exchange(nullptr);
                if (--_threadsInPop == 0)
                {
                    DeleteNodes(nodesToDelete);
                }
                else if (nodesToDelete)
                {
                    ChainPendingNodes(nodesToDelete);
                }
                delete oldHead;
            }
            else
            {
                ChainPendingNode(oldHead);
                --_threadsInPop;
            }
        }

        void ChainPendingNodes(Node *nodes)
        {
            Node *last = nodes;
            while (last->Next)
                last = last->Next;
            ChainPendingNodes(nodes, last);
        }

        void ChainPendingNodes(Node *first, Node *last)
        {
            last->Next = _toBeDeleted.load();
            while (!_toBeDeleted.compare_exchange_weak(last->Next, first))
            {
            }
        }

        void ChainPendingNode(Node *node)
        {
            ChainPendingNodes(node, node);
        }

        static void DeleteNodes(Node *nodes)
        {
            while (nodes)
            {
                Node *next = nodes->Next;
                delete nodes;
                nodes = next;
            }
        }
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
