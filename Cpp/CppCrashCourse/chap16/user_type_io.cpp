#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class Person
{
public:
    Person(string name, string addr, string phoneNum) : name{name}, addr{addr}, phoneNum{phoneNum} {}
    string name;
    string addr;
    string phoneNum;
};

ostream& operator<<(ostream& os, const Person& p)
{
    os << "A guy named " << p.name << " lives in " << p.addr
        << ", whose phone number is " << p.phoneNum << ".";
    return os;
}

int main(void)
{
    Person p1{"Gavin", "Anhui", "13734567890"};
    Person p2{"Echo", "Guangdong", "18665430987"};
    cout << p1 << "\n" << p2 << endl;
}