#include <cassert>
#include <cctype>
#include <iostream>
#include <string>

int main()
{
    using std::cout;
    using std::string;

    cout << std::boolalpha;

    // Char category check in <cctype>.
    cout << static_cast<bool>(std::isspace(' ')) << ' '
         << static_cast<bool>(std::isspace('\t')) << '\n';
    cout << static_cast<bool>(std::isalpha('a')) << ' '
         << static_cast<bool>(std::isalpha('Z')) << ' '
         << static_cast<bool>(std::isalpha('0')) << '\n';
    cout << static_cast<bool>(std::isdigit('1')) << ' '
         << static_cast<bool>(std::isdigit('5')) << ' '
         << static_cast<bool>(std::isdigit('A')) << '\n';
    cout << static_cast<bool>(std::isxdigit('1')) << ' '
         << static_cast<bool>(std::isxdigit('A')) << ' '
         << static_cast<bool>(std::isxdigit('F')) << ' '
         << static_cast<bool>(std::isxdigit('G')) << '\n';
    cout << static_cast<bool>(std::isupper('A')) << ' '
         << static_cast<bool>(std::isupper('a')) << ' '
         << static_cast<bool>(std::isupper('0')) << '\n';
    cout << static_cast<bool>(std::islower('A')) << ' '
         << static_cast<bool>(std::islower('a')) << ' '
         << static_cast<bool>(std::islower('0')) << '\n';
    cout << static_cast<bool>(std::isalnum('A')) << ' '
         << static_cast<bool>(std::isalnum('4')) << ' '
         << static_cast<bool>(std::isalnum('z')) << '\n';
    cout << static_cast<bool>(std::iscntrl('\r')) << ' '
         << static_cast<bool>(std::iscntrl('a')) << ' '
         << static_cast<bool>(std::iscntrl('\b')) << '\n';
    cout << static_cast<bool>(std::ispunct(',')) << ' '
         << static_cast<bool>(std::ispunct(':')) << ' '
         << static_cast<bool>(std::ispunct('\n')) << '\n';

    // String constructors.
    string s1{"Hello World"};
    const char *const cs = "The C++ Programming Language";
    string s2{s1, 6};
    assert(s2 == "World");
    string s3{s1, 2, 3};
    assert(s3 == "llo");
    string s4{s1.cbegin(), s1.cbegin() + 2};
    assert(s4 == "He");
    string s5{cs + 4, 3};
    assert(s5 == "C++");
    string s6(5, 'f'); // Must use brackets instead of braces here.
    assert(s6 == "fffff");

    // Conversion to/from numbers.
    assert(std::stoi("123") == int{123});
    assert(std::stol("123") == long{123});
    assert(std::stoll("123") == 123LL);
    assert(std::stoull("123") == 123ULL);
    assert(std::stof("123.456") == 123.456F);
    assert(std::stod("123.456") == 123.456);

    // Other ops.
    string s{};
    s.assign(s1);
    assert(s == "Hello World");
    s.assign(s1, 6, 5);
    assert(s == "World");
    s.assign(s1.cbegin(), s1.cend() - 2);
    assert(s == "Hello Wor");
    s.assign(3, 'x');
    assert(s == "xxx");
    s.assign(cs, 3);
    assert(s == "The");
    s.append(cs + 3, 4);
    assert(s == "The C++");
    s.append(" Language");
    assert(s == "The C++ Language");
    s = "C";
    s.append(2, '+');
    assert(s == "C++");
    s.insert(0, "The ");
    assert(s == "The C++");
    s.insert(s.begin() + 4, 3, 'o');
    assert(s == "The oooC++");
    s.erase(4, 3);
    assert(s == "The C++");
    s.erase(3);
    assert(s == "The");
    s.replace(0, 3, "C++");
    assert(s == "C++");
    assert(s.find('C') == 0);
    assert(s.find('c') == string::npos);
    assert(s.rfind('+') == 2);
    s = s1;
    assert(s.substr(6) == "World");
    assert(s.substr(0, 5) == "Hello");
}
