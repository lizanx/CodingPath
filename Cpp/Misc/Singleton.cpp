#include <iostream>
#include <string_view>

namespace
{
    class Logger
    {
    private:
        Logger() = default;

    public:
        // Make sure to delete default-generated copy/move ctor!!!
        Logger(const Logger &) = delete;
        Logger(Logger &&) = delete;
        Logger &operator=(const Logger &) = delete;
        Logger &operator=(Logger &&) = delete;
        ~Logger() = default;

        static Logger &GetInstance()
        {
            static Logger logger{};
            return logger;
        }

        void Info(std::string_view sv) const
        {
            std::cout << "[INFO] " << sv << "\n";
        }

        void Warn(std::string_view sv) const
        {
            std::cout << "[WARN] " << sv << "\n";
        }

        void Error(std::string_view sv) const
        {
            std::cout << "[ERROR] " << sv << "\n";
        }
    };

}

int main()
{
    // Case 1
    auto &logger1 = Logger::GetInstance();
    logger1.Info("Logger1 - info");
    auto &logger2 = Logger::GetInstance();
    logger2.Warn("Logger2 - warn");
    std::cout << "logger1 == logger2 ? -> " << (&logger1 == &logger2 ? "True" : "False") << "\n";

    // Case 2
    auto &logger3 = Logger::GetInstance();
    logger3.Info("Logger3 - info");
    auto logger4 = Logger::GetInstance(); // Copy here !!!
    logger4.Warn("Logger4 - warn");
    std::cout << "logger3 == logger4 ? -> " << (&logger3 == &logger4 ? "True" : "False") << "\n";

    return 0;
}
