#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main(void)
{
    string str{};
    for (;;)
    {
        cout << "Please enter your word: ";
        cin >> str;
        if (str == "quit")
            break;
        transform(str.begin(), str.end(), str.begin(), ::toupper);
        cout << "Converted to upper case: " << str << "\n";
    }
}