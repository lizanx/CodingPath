#include <fstream>
#include <iostream>
#include <string>
#include <sys/stat.h>

static constexpr const char *const file1 = "file1.txt";
static constexpr const char *const file2 = "file2.txt";

static bool checkRegularFile(const char *const filePath)
{
    struct stat info;
    if (::stat(filePath, &info) != 0)
        return false; // no access right
    if (info.st_mode & S_IFDIR)
        return false; // is directory
    std::ifstream fin{filePath};
    if (!fin.is_open() || !fin.good())
        return false;
    try
    {
        char c = fin.get();
    }
    catch (std::ios_base::failure &)
    {
        return false;
    }
    return true;
}

static long long getFileSize(const char *const filePath)
{
    std::ifstream fin{filePath};
    fin.seekg(0, std::ios_base::beg);
    auto startPos = fin.tellg();
    fin.seekg(0, std::ios_base::end);
    auto endPos = fin.tellg();

    return endPos - startPos;
}

int main()
{
    std::ifstream fs{file1};
    std::string str{};

    while (std::getline(fs, str))
    {
        std::cout << "getline: " << str << "\n";
    };
    fs.close();
    std::cout << "\n\n--------------------------\n\n";

    fs.open(file1);
    while (fs.peek() != std::char_traits<char>::eof())
    {
        char c;
        fs >> c; // This will skip white spaces by default
        std::cout << c;
    }
    fs.close();
    std::cout << "\n\n--------------------------\n\n";

    fs.open(file2);
    while (true)
    {
        char c = fs.get(); // This will reserve white spaces
        if (fs.eof())
            break;
        std::cout << c;
    }
    fs.close();
    std::cout << "\n\n--------------------------\n\n";

    std::cout << "fil1 is regular file: " << std::boolalpha << checkRegularFile(file1) << "\n"
              << "fil2 is regular file: " << checkRegularFile(file2) << "\n"
              << "fil3 is regular file: " << checkRegularFile("file3.txt") << "\n";

    std::cout << "Size of file1: " << getFileSize(file1) << "\n"
              << "Size of file2: " << getFileSize(file2) << "\n";
}
