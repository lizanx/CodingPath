#include <iostream>
#include <boost/asio.hpp>

int main(void)
{
    boost::asio::io_context ctx{};
    boost::asio::ip::tcp::resolver resolver{ ctx };
    boost::system::error_code ec{};

    for (auto&& result : resolver.resolve("www.qq.com", "https", ec))
    {
        std::cout << result.service_name() << "\t"
            << result.host_name() << "\t"
            << result.endpoint() << std::endl;
    }

    std::cout << "\n\nAsync resolve version:\n";
    resolver.async_resolve("www.qq.com", "https", [](boost::system::error_code err, const auto& results) {
        if (err)
        {
            std::cerr << "Error: " << err << std::endl;
            return;
        }
        for (auto&& result : results)
        {
            std::cout << "Async: "
                << result.service_name() << "\t"
                << result.host_name() << "\t"
                << result.endpoint() << std::endl;
        }
    });
    ctx.run();
}