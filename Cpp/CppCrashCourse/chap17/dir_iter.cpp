#include <iostream>
#include <filesystem>

using namespace std;
using namespace std::filesystem;

struct Attribute
{
    Attribute& operator+=(const Attribute &other_attr)
    {
        this->size_bytes += other_attr.size_bytes;
        this->n_dirs += other_attr.n_dirs;
        this->n_files += other_attr.n_files;
        return *this;
    }

    size_t size_bytes;
    size_t n_dirs;
    size_t n_files;
};

void print_path_attr(const Attribute& attr, string_view path)
{
    cout << setw(14) << attr.size_bytes
        << setw(7) << attr.n_files
        << setw(7) << attr.n_dirs
        << " " << path << "\n";
}

Attribute explore(const directory_entry& de)
{
    Attribute attr{};

    for (const auto& dir_entry : recursive_directory_iterator{ de.path() })
    {
        if (dir_entry.is_directory())
        {
            attr.n_dirs++;
        }
        else
        {
            attr.n_files++;
            attr.size_bytes += dir_entry.file_size();
        }
    }

    return attr;
}

int main(int argc, const char* argv[])
{
    if (argc != 2)
    {
        cerr << "You must enter a path." << endl;
        return 0;
    }

    const path p{ argv[1] };
    cout << "Size           Files   Dirs    Name\n";
    cout << "-------------- ------- ------- ----\n";
    Attribute root_attr{};
    for (const auto& de : directory_iterator{ p })
    {
        try
        {
            if (de.is_directory())
            {
                const auto attr = explore(de);
                root_attr += attr;
                print_path_attr(attr, de.path().string());
                root_attr.n_dirs++;
            }
            else
            {
                root_attr.n_files++;
                error_code ec{};
                root_attr.size_bytes += de.file_size(ec);
                if (ec)
                {
                    cerr << "Error reading file size: " << de.path() << endl;
                }
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    print_path_attr(root_attr, p.string());
}