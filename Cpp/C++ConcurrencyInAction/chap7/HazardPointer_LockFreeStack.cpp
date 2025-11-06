#include <atomic>
#include <chrono>
#include <functional>
#include <iostream>
#include <memory>
#include <random>
#include <stdexcept>
#include <syncstream>
#include <thread>

namespace
{
    constexpr unsigned MAX_HAZARD_POINTERS = 100;
    struct HazardPointer
    {
        std::atomic<std::thread::id> Id{};
        std::atomic<void *> Pointer{};
    };
    HazardPointer g_HazardPointers[MAX_HAZARD_POINTERS];

    class HazardPointerOwner
    {
    public:
        HazardPointerOwner()
        {
            for (unsigned i = 0; i < MAX_HAZARD_POINTERS; ++i)
            {
                std::thread::id oldId{};
                if (g_HazardPointers[i].Id.compare_exchange_strong(oldId, std::this_thread::get_id()))
                {
                    _hp = &g_HazardPointers[i];
                    break;
                }
            }
            if (!_hp)
                throw std::runtime_error{"No hazard pointers available!"};
        }
        HazardPointerOwner(const HazardPointerOwner &) = delete;
        HazardPointerOwner &operator=(const HazardPointerOwner &) = delete;
        ~HazardPointerOwner()
        {
            _hp->Pointer.store(nullptr);
            _hp->Id.store(std::thread::id{});
        }

        std::atomic<void *> &GetPointer()
        {
            return _hp->Pointer;
        }

    private:
        HazardPointer *_hp{};
    };

    std::atomic<void *> &GetHazardPointerForCurrentThread()
    {
        thread_local static HazardPointerOwner hazardPtrOwner{};
        return hazardPtrOwner.GetPointer();
    }

    bool OutstandingHazardPointersFor(void *p)
    {
        for (unsigned i = 0; i < MAX_HAZARD_POINTERS; ++i)
        {
            if (g_HazardPointers[i].Pointer.load() == p)
                return true;
        }
        return false;
    }

    template <typename T>
    void DoDelete(void *p)
    {
        delete static_cast<T *>(p);
    }

    struct DataToReclaim
    {
        void *Data;
        std::function<void(void *)> Deleter;
        DataToReclaim *Next;

        template <typename T>
        DataToReclaim(T *p) : Data{p}, Deleter{&DoDelete<T>}, Next{nullptr}
        {
        }

        ~DataToReclaim()
        {
            Deleter(Data);
        }
    };

    std::atomic<DataToReclaim *> g_NodesToReclaim{};

    void AddToReclaimList(DataToReclaim *node)
    {
        node->Next = g_NodesToReclaim.load();
        while (!g_NodesToReclaim.compare_exchange_weak(node->Next, node))
        {
        }
    }

    template <typename T>
    void ReclaimLater(T *data)
    {
        AddToReclaimList(new DataToReclaim{data});
    }

    void DeleteNodesWithNoHazards()
    {
        DataToReclaim *current = g_NodesToReclaim.exchange(nullptr);
        while (current)
        {
            DataToReclaim *next = current->Next;
            if (!OutstandingHazardPointersFor(current->Data))
                delete current;
            else
                AddToReclaimList(current);
            current = next;
        }
    }

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
            std::atomic<void *> &hazardPtr = GetHazardPointerForCurrentThread();
            Node *oldHead = _head.load();
            do
            {
                Node *tmp{};
                do
                {
                    tmp = oldHead;
                    hazardPtr.store(oldHead);
                    oldHead = _head.load();
                } while (oldHead != tmp);

            } while (oldHead && !_head.compare_exchange_strong(oldHead, oldHead->Next));
            hazardPtr.store(nullptr);
            std::shared_ptr<T> result{};
            if (oldHead)
            {
                result.swap(oldHead->Data);
                if (OutstandingHazardPointersFor(oldHead))
                {
                    ReclaimLater(oldHead);
                }
                else
                {
                    delete oldHead;
                }
                DeleteNodesWithNoHazards();
            }
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
