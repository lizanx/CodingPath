#include <iostream>
#include <filesystem>
#include <string>

using namespace std;
using namespace filesystem;

int main(int argc, const char* argv[])
{
    if (argc != 3)
    {
        cerr << "Usage: path extension\n";
        return 0;
    }

    string extension{ argv[2] };
    path input_path{ argv[1] };
    error_code ec{};
    directory_entry entry{ input_path, ec };
    if (!entry.is_directory())
    {
        if (entry.path().extension() == extension)
        {
            cout << entry.path().string() << endl;
        }
        return 0;
    }
    for (const auto& de : recursive_directory_iterator(input_path))
    {
        if (de.is_regular_file() && de.path().extension() == extension)
        {
            cout << de.path().string() << "\n";
        }
    }
}