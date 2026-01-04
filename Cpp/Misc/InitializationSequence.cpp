#include <iostream>

namespace
{
    using std::cout;

    class Data
    {
    public:
        Data(int data) : _data{data}
        {
            cout << "Initializing Data -> " << _data << "\n";
        }

        Data() : Data{0}
        {
        }

        int Get() const
        {
            return _data;
        }

    private:
        int _data;
    };

    class Base
    {
    public:
        Base(int data) : _d2{data}
        {
            cout << "Base::Ctor\n";
            DisplayData();
        }

        virtual void DisplayData() const
        {
            cout << "Base::d1 -> " << _d1.Get() << "\n"
                 << "Base::d2 -> " << _d2.Get() << "\n";
        }

    private:
        Data _d1{1};
        Data _d2;
    };

    class Derived : public Base
    {
    public:
        Derived(int d2, int d3) : Base{d2}, _d3{d3}
        {
            cout << "Derived::Ctor\n";
            DisplayData();
        }

        Derived() : Derived{2, 3}
        {
        }

        virtual void DisplayData() const override
        {
            cout << "Derived::d3 -> " << _d3.Get() << "\n"
                 << "Derived::d4 -> " << _d4.Get() << "\n";
        }

    private:
        Data _d3;
        Data _d4{4};
    };

}

int main()
{
    Derived d{};
    return 0;
}
