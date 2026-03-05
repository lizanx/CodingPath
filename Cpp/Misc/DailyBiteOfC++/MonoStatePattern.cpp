#include <mutex>
#include <print>
#include <string>

namespace
{
    using std::string;

    class MonoConfig
    {
    public:
        MonoConfig();
        int GetIntData() const;
        string GetStringData() const;

    private:
        static std::once_flag _flag;
        static void PopulateConfig();
        static uint64_t _intData;
        static string _strData;
    };

    std::once_flag MonoConfig::_flag{};
    uint64_t MonoConfig::_intData{};
    string MonoConfig::_strData{};

    MonoConfig::MonoConfig()
    {
        std::call_once(_flag, PopulateConfig);
    }

    int MonoConfig::GetIntData() const
    {
        return _intData;
    }

    string MonoConfig::GetStringData() const
    {
        return _strData;
    }

    void MonoConfig::PopulateConfig()
    {
        _intData = 22;
        _strData = "Hello world";
    }

    void PrintMonoConfig(std::string_view tag, const MonoConfig &cfg) noexcept
    {
        std::println("{}: int-data -> {}, string-data -> {}", tag, cfg.GetIntData(), cfg.GetStringData());
    }
}

int main()
{
    MonoConfig cfg{};
    PrintMonoConfig("cfg", cfg);

    // You can create multple instances of "MonoConfig", which is different compared to Singleton pattern.
    MonoConfig c1{}, c2{}, c3{};
    PrintMonoConfig("c1", c1);
    PrintMonoConfig("c2", c2);
    PrintMonoConfig("c3", c3);

    return 0;
}
