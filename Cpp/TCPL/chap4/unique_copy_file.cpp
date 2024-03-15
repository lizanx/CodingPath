#include <iostream>
#include <fstream>
#include <set>
#include <filesystem>
#include <string>
#include <iterator>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "You must enter two file paths "
            << "where the first is source file "
            << "and the second is destination file."
            << std::endl;
        return 0;
    }

    std::string srcFile{ argv[1] }, dstFile{ argv[2] };

    if (!std::filesystem::exists(srcFile))
    {
        std::cerr << "The source file " << srcFile
            << " doesn't exist!\n";
        return 0;
    }

    if (!std::filesystem::is_regular_file(srcFile))
    {
        std::cerr << "The files aren't all regular files!\n";
        return 0;
    }

    std::ifstream ifs{ srcFile };
    std::ofstream ofs{ dstFile };
    std::set<std::string> wordsSet(
        std::istream_iterator<std::string>{ ifs },
        std::istream_iterator<std::string>{}
    );
    std::copy(wordsSet.begin(), wordsSet.end(), std::ostream_iterator<std::string>{ ofs });

    return !ifs.eof() || !ofs;
}
