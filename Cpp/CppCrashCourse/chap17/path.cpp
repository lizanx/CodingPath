#include <iostream>
#include <filesystem>
#include <chrono>

static void describe_path(const std::filesystem::path& p)
{
    std::cout << std::boolalpha << "Path: " << p << std::endl;
    try
    {
        std::cout << "Is directory: " << std::filesystem::is_directory(p) << std::endl;
        std::cout << "Is regular file: " << std::filesystem::is_regular_file(p) << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << '\n';
    }
}

static void write_info(const std::filesystem::path& p)
{
    if (!std::filesystem::exists(p))
    {
        std::cout << p << " doesn't exist!" << std::endl;
        return;
    }
    const auto last_write_time = std::filesystem::last_write_time(p).time_since_epoch();
    const auto last_write_hours = std::chrono::duration_cast<std::chrono::hours>(last_write_time);
    std::cout << p << "\tLast Modified: " << last_write_hours.count()
        << "\tSize: " << std::filesystem::file_size(p) << std::endl;
}

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

    std::cout << "\n --- File/directory check ---\n";
    std::filesystem::path win_path{ R"(C:/Windows/System32/kernel32.dll)" };
    describe_path(win_path);
    win_path.remove_filename();
    describe_path(win_path);
    std::filesystem::path unix_path{ R"(/bin/bash)" };
    describe_path(unix_path);
    unix_path.remove_filename();
    describe_path(unix_path);

    std::cout << "\n --- File info and modificatiion ---\n";
    unix_path = std::filesystem::path{R"(/bin/bash)"};
    const auto readme_path = std::filesystem::temp_directory_path().append("README");
    try
    {
        write_info(unix_path);
        write_info(readme_path);

        std::cout << "Copying " << unix_path.filename()
            << " to " << readme_path << "\n";
        std::filesystem::copy_file(unix_path, readme_path);
        write_info(readme_path);

        std::cout << "Resizing " << readme_path.filename() << "\n";
        std::filesystem::resize_file(readme_path, 1024);
        write_info(readme_path);

        std::cout << "Removing " << readme_path.filename() << "\n";
        std::filesystem::remove(readme_path);
        write_info(readme_path);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << '\n';
    }
    
}
