#include <iostream>
#include <mutex>
#include <stdexcept>

namespace
{
    using std::size_t;

    class HierarchyViolationException : public std::runtime_error
    {
    public:
        HierarchyViolationException() : runtime_error{"Hierarchy violation"}
        {
        }
    };

    class HierarchicalMutex
    {
    private:
        const size_t _lockLevel;
        size_t _previousLockLevel{};
        static thread_local size_t s_ThreadLockLevel;
        std::mutex _mutex{};

        void CheckForHierarchyViolation() const
        {
            if (s_ThreadLockLevel <= _lockLevel)
                throw HierarchyViolationException{};
        }

        void UpdateHierarchyLevel()
        {
            _previousLockLevel = s_ThreadLockLevel;
            s_ThreadLockLevel = _lockLevel;
        }

    public:
        explicit HierarchicalMutex(size_t lockLevel) : _lockLevel{lockLevel}
        {
        }

        void lock()
        {
            CheckForHierarchyViolation();
            _mutex.lock();
            UpdateHierarchyLevel();
        }

        void unlock()
        {
            if (s_ThreadLockLevel != _lockLevel)
                throw HierarchyViolationException{};
            s_ThreadLockLevel = _previousLockLevel;
            _mutex.unlock();
        }

        bool try_lock()
        {
            CheckForHierarchyViolation();
            if (!_mutex.try_lock())
                return false;
            UpdateHierarchyLevel();
            return true;
        }
    };

    void DemoFn(int id, HierarchicalMutex &m1, HierarchicalMutex &m2)
    {
        try
        {
            std::lock_guard lck1{m1};
            std::lock_guard lck2{m2};
            std::cout << "DemoFn-" << id << " successfully locks m1 and m2\n";
        }
        catch (const HierarchyViolationException &e)
        {
            std::cout << "DemoFn-" << id << " Exception(HierarchyViolation): " << e.what() << "\n";
        }
        catch (...)
        {
            std::cout << "DemoFn-" << id << " Unknown exception\n";
        }
    }

    thread_local size_t HierarchicalMutex::s_ThreadLockLevel{std::numeric_limits<size_t>::max()};
}

int main(int argc, char *argv[])
{
    HierarchicalMutex m1{1000}, m2{100}, m3{100}, m4{10};
    DemoFn(1, m1, m2); // OK
    DemoFn(2, m2, m1); // Fail
    DemoFn(3, m2, m2); // Fail
    DemoFn(4, m3, m4); // OK
    DemoFn(5, m4, m1); // Fail
}
