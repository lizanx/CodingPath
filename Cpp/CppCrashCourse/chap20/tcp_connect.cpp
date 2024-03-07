#include <iostream>
#include <boost/asio.hpp>

int main(void)
{
    boost::asio::io_context ctx{};
    boost::asio::ip::tcp::resolver resolver{ ctx };
    boost::asio::ip::tcp::socket socket{ ctx };

    try
    {
        auto endpoints = resolver.resolve("www.qq.com", "https");
        const auto connectedEndpoint = boost::asio::connect(socket, endpoints);
        std::cout << "Connected endpoint is " << connectedEndpoint << std::endl;
    }
    catch(boost::system::system_error& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    std::cout << "\nAsync connect:\n";
    boost::asio::async_connect(
        socket,
        resolver.resolve("www.qq.com", "https"),
        [](boost::system::error_code ec, const auto& endpoint) {
            std::cout << "Async connected endpoint is " << endpoint << std::endl;
        }
    );
    ctx.run();
}