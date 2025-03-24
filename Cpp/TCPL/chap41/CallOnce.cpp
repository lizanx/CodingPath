#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

namespace
{
    class Singleton
    {
    public:
        static Singleton &GetInstance();
        void DoSomething();

    private:
        Singleton();
        ~Singleton();

        static void Init();
        static void Destroy(Singleton *ps);
        static std::unique_ptr<Singleton, void (*)(Singleton *)> _ptr;
        static std::once_flag _once_flag;
    };

    Singleton &Singleton::GetInstance()
    {
        std::call_once(_once_flag, Init);
        return *_ptr;
    }

    void Singleton::DoSomething()
    {
        std::cout << "Singleton::DoSomething\n";
    }

    Singleton::Singleton()
    {
        std::cout << "Constrcuting Singleton\n";
    }

    Singleton::~Singleton()
    {
        std::cout << "Destrcuting Singleton\n";
    }

    void Singleton::Init()
    {
        _ptr.reset(new Singleton{});
    }

    void Singleton::Destroy(Singleton *ps)
    {
        ps->~Singleton();
    }

    std::unique_ptr<Singleton, void (*)(Singleton *)> Singleton::_ptr{nullptr, &Singleton::Destroy};
    std::once_flag Singleton::_once_flag{};
}

int main()
{
    auto fn = [](Singleton &s)
    { s.DoSomething(); };

    std::thread t1{fn, std::ref(Singleton::GetInstance())};
    std::thread t2{fn, std::ref(Singleton::GetInstance())};
    std::thread t3{fn, std::ref(Singleton::GetInstance())};
    std::thread t4{fn, std::ref(Singleton::GetInstance())};
    std::thread t5{fn, std::ref(Singleton::GetInstance())};

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
}
