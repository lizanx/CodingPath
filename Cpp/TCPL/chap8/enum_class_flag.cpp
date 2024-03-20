#include <iostream>
#include <map>

enum class ErrFlag : unsigned
{
    ErrNone = 0,
    ErrOne = 1,
    ErrTwo = 2,
    ErrThree = 4,
    ErrFour = 8,
};

static std::map<ErrFlag, std::string> errMap{
    { ErrFlag::ErrNone, "No error"},
    { ErrFlag::ErrOne, "1st error"},
    { ErrFlag::ErrTwo, "2nd error"},
    { ErrFlag::ErrThree, "3rd error"},
    { ErrFlag::ErrFour, "4th error"},
};

std::ostream& operator<<(std::ostream& os, ErrFlag flag)
{
    os << errMap[flag];
    return os;
}

constexpr ErrFlag operator|(ErrFlag f1, ErrFlag f2)
{
    return static_cast<ErrFlag>(static_cast<unsigned>(f1) | static_cast<unsigned>(f2));
}

constexpr ErrFlag operator&(ErrFlag f1, ErrFlag f2)
{
    return static_cast<ErrFlag>(static_cast<unsigned>(f1) & static_cast<unsigned>(f2));
}

int main()
{
    ErrFlag f1 = ErrFlag::ErrNone;
    ErrFlag f2 = ErrFlag::ErrThree;

    switch (f1 & f2)
    {
    case ErrFlag::ErrNone:
        std::cout << "No error for &\n";
        break;
    default:
        std::cout << "Error for &: " << (f1 & f2) << "\n";
        break;
    }

    switch (f1 | f2)
    {
    case ErrFlag::ErrNone:
        std::cout << "No error for |\n";
        break;
    default:
        std::cout << "Error for |: " << (f1 | f2) << "\n";
        break;
    }
}