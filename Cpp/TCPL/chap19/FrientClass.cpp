#include <iostream>

class A;

class B
{
public:
    int getAData1(const A &a) const;
    int getAData2(const A &a) const;
    int getFrientAData2(const A &a) const;
};

static int getFriendAData2(const A &a);

class C;

class A
{
public:
    explicit A(int d1, int d2);
    int getData1() const;
    friend int B::getFrientAData2(const A &) const;
    friend int getFriendAData2(const A &a);
    friend class C;

private:
    int m_data_1;
    int m_data_2;
};

class C
{
public:
    int getAData1(const A &a) const;
    int getAData2(const A &a) const;
};

A::A(int d1, int d2) : m_data_1{d1}, m_data_2{d2}
{
}

int A::getData1() const
{
    return m_data_1;
}

int B::getAData1(const A &a) const
{
    return a.getData1();
}

int B::getAData2(const A &a) const
{
    // Cannot access A's private data.
    // return a.m_data_2;

    return 0;
}

int B::getFrientAData2(const A &a) const
{
    return a.m_data_2;
}

static int getAData2(const A &a)
{
    // Cannot access A's private data.
    // return a.m_data_2;

    return 0;
}

static int getFriendAData2(const A &a)
{
    return a.m_data_2;
}

int C::getAData1(const A &a) const
{
    return a.m_data_1;
}

int C::getAData2(const A &a) const
{
    return a.m_data_2;
}

int main(int argc, char *argv[])
{
    A a{1, 2};
    B b{};
    C c{};

    std::cout << "::getAData2 -> " << ::getAData2(a) << "\n"
              << "::getFriendAData2 -> " << ::getFriendAData2(a) << "\n"
              << "B::getAData1 -> " << b.getAData1(a) << "\n"
              << "B::getAData2 -> " << b.getAData2(a) << "\n"
              << "B::getFrientAData2 -> " << b.getFrientAData2(a) << "\n"
              << "(friend class)C::getAData1 -> " << c.getAData1(a) << "\n"
              << "(friend class)C::getAData2 -> " << c.getAData2(a) << "\n";
}
