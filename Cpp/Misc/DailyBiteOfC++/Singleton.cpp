#include <cassert>

namespace
{
    class Singleton
    {
    public:
        int GetData() const noexcept
        {
            return m_data;
        }

    private:
        int m_data;

        Singleton(int data) : m_data{data}
        {
        }

        Singleton(const Singleton &) = default;
        Singleton(Singleton &&) = default;
        Singleton &operator=(const Singleton &) = delete;
        Singleton &operator=(Singleton &&) = delete;

        friend Singleton &SingletonGetInstance();
    };

    Singleton &SingletonGetInstance()
    {
        static Singleton singleton{10};
        return singleton;
    }
}

int main()
{
    auto &a = SingletonGetInstance();
    assert(a.GetData() == 10);
    auto &b = SingletonGetInstance();
    assert(b.GetData() == 10);
    assert(&a == &b);

    // auto c = SingletonGetInstance();
    // assert(c.GetData() == 10);

    return 0;
}
