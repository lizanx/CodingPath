#include <iostream>
#include <filesystem>

int main(void)
{
    std::filesystem::path p{"/Users/lizan/Dev/CodingPath/Cpp/CppCrashCourse/chap17/path.cpp"};
    std::cout << "Root name: " << p.root_name()
        << "\nRoot directory: " << p.root_directory()
        << "\nRoot path: " << p.root_path()
        << "\nRelative path: " << p.relative_path()
        << "\nParent path: " << p.parent_path()
        << "\nFilename: " << p.filename()
        << "\nStem: " << p.stem()
        << "\nExtension: " << p.extension()
        << std::endl;
    
    std::cout << "\n --- Relative/absolute/temp path ---\n";
    const auto temp_path = std::filesystem::temp_directory_path();
    const auto relative = std::filesystem::relative(temp_path);
    std::cout << std::boolalpha
        << "Temporary dir path: " << temp_path
        << "\nTemp dir absolute: " << temp_path.is_absolute()
        << "\nCurrent path: " << std::filesystem::current_path()
        << "\nTemp dir's relative path: " << relative
        << "\nRelative path absolute: " << relative.is_absolute()
        << "\nChanging current dir to temp...";
    std::filesystem::current_path(temp_path);
    std::cout << "\nCurrent directory: " << std::filesystem::current_path();
}
