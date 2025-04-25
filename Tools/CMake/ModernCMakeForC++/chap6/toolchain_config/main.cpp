#include <iostream>

int main(int argc, char *argv[])
{
#if defined(PLATFORM_WIN)
    std::cout << "Compiling on Windows...\n";
#elif defined(PLATFORM_LINUX)
    std::cout << "Compiling on Linux...\n";
#endif

#if defined(COMPILER_GCC)
    std::cout << "Using GCC compiler...\n";
#elif defined(COMPILER_CLANG)
    std::cout << "Using Clang(LLVM) compiler...\n";
#endif

#if defined(CONFIG_DEBUG)
    std::cout << "Config: debug\n";
#elif defined(CONFIG_RELEASE)
    std::cout << "Config: release\n";
#endif
}
