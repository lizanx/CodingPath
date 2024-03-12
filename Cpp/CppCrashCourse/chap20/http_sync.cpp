#include <string>
#include <iostream>
#include <sstream>
#include <boost/asio.hpp>

std::string request(std::string host, boost::asio::io_context &ctx)
{
    std::stringstream requestStream{};
    requestStream << "GET / HTTP/1.1\r\n"
                    "Host: "
                    << host
                    << "\r\n"
                    "Accept: text/html\r\n"
                    "Accept-Language: en-us\r\n"
                    "Accept-Encoding: identity\r\n"
                    "Connection: close\r\n\r\n";
    const auto request = requestStream.str();
    boost::asio::ip::tcp::resolver resolver{ ctx };
    const auto endpoints = resolver.resolve(host, "http");
    boost::asio::ip::tcp::socket socket{ ctx };
    const auto connectedEndpoint = boost::asio::connect(socket, endpoints);
    std::cout << "Connected enpoint: " << connectedEndpoint << std::endl;
    boost::asio::write(socket, boost::asio::buffer(request));

    std::string response{};
    boost::system::error_code ec{};
    boost::asio::read(socket, boost::asio::dynamic_buffer(response), ec);
    if (ec && ec.value() != 2)
    {
        throw boost::system::system_error{ ec };
    }
    return response;
}

int main()
{
    boost::asio::io_context ctx{};
    try
    {
        const auto result = request("www.stackoverflow.com", ctx);
        std::cout << "Response:\n" << result << std::endl;
    }
    catch(const boost::system::system_error& se)
    {
        std::cerr << "Error: " << se.what() << '\n';
    }
}
