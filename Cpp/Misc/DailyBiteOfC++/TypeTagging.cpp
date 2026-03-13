// If two functions have exactly the same name and arguments, you use the method demonstrated below to resolve the problem.
#include <string>
#include <print>

namespace
{
    struct IPv4Tag
    {
    };
    struct IPv6Tag
    {
    };

    constexpr inline IPv4Tag IPv4{};
    constexpr inline IPv6Tag IPv6{};

    class IPAddress
    {
    public:
        IPAddress(IPv4Tag tag, std::string addr, int port)
        {
            std::println("[IPv4] Addr: {}, port: {}", addr, port);
        }

        IPAddress(IPv6Tag tag, std::string addr, int port)
        {
            std::println("[IPv6] Addr: {}, port: {}", addr, port);
        }
    };
}

int main()
{
    IPAddress addr1{IPv4, "127.0.0.1", 80};
    IPAddress addr2{IPv6, "::1", 80};

    return 0;
}
