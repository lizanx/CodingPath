#include <filesystem>
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "You should enter a directory/file path!\n";
        return EXIT_FAILURE;
    }

    namespace fs = std::filesystem;
    fs::path inputPath{argv[1]};

    if (!fs::exists(inputPath))
    {
        std::cerr << "The input path " << inputPath << " doesn't exist!\n";
        return EXIT_FAILURE;
    }

    if (fs::is_regular_file(inputPath))
    {
        std::cout << "It's a regular file of size "
                  << fs::file_size(inputPath) << " bytes.\n";
        std::cout << "Root name: " << inputPath.root_name() << "\n"
                  << "Root directory: " << inputPath.root_directory() << "\n"
                  << "Root path: " << inputPath.root_path() << "\n"
                  << "Parent path: " << inputPath.parent_path() << "\n"
                  << "File name: " << inputPath.filename() << "\n"
                  << "File extension: " << inputPath.extension() << "\n";
    }
    else if (fs::is_directory(inputPath))
    {
        std::cout << "It's a directory, empty = " << std::boolalpha
                  << fs::is_empty(inputPath) << "\n";
        std::cout << "Looping through each file...\n";
        for (auto &subPath : fs::recursive_directory_iterator(inputPath))
        {
            if (subPath.is_block_file())
                std::cout << "\t" << subPath.path() << " is block file.\n";
            else if (subPath.is_character_file())
                std::cout << "\t" << subPath.path() << " is character file.\n";
            else if (subPath.is_directory())
                std::cout << "\t" << subPath.path() << " is directory, "
                          << "empty = " << fs::is_empty(subPath.path()) << ".\n";
            else if (subPath.is_symlink())
                std::cout << "\t" << subPath.path() << " is symbol link.\n";
            else if (subPath.is_regular_file())
                std::cout << "\t" << subPath.path() << " is regular file, size = "
                          << subPath.file_size() << " bytes\n";
        }
    }
}