#include <string>
#include <iostream>
#include <sstream>
#include <boost/asio.hpp>

using ResolveResult = boost::asio::ip::tcp::resolver::results_type;
using Endpoint = boost::asio::ip::tcp::endpoint;

struct Request
{
    explicit Request(std::string host, boost::asio::io_context& ctx)
        : resolver{ ctx }, socket{ ctx }, host{ std::move(host) }
        {
            std::stringstream requestStream{};
            requestStream << "GET / HTTP1.1\r\n"
                    << "Host: " << host << "\r\n"
                    << "Accept: text/html\r\n"
                    << "Accept-Language: en-us\r\n"
                    << "Accept-Encoding: identity\r\n"
                    << "Connection: close\r\n\r\n";
            request = requestStream.str();
            resolver.async_resolve(this->host, "https",
                [this](boost::system::error_code ec, const ResolveResult& results) {
                    ResolutionHandler(ec, results);
                }
            );
        }

    void ResolutionHandler(boost::system::error_code ec, const ResolveResult& results)
    {
        if (ec)
        {
            std::cerr << "Error resolve " << host << ": " << ec.message() << std::endl;
            return;
        }
        boost::asio::async_connect(socket, results,
            [this](boost::system::error_code ec, const Endpoint& endpoint) {
                ConnectionHandler(ec, endpoint);
            });
    }

    void ConnectionHandler(boost::system::error_code ec, const Endpoint& endpoint)
    {
        if (ec)
        {
            std::cerr << "Error connect to " << host << ": " << ec.message() << std::endl;
            return;
        }
        boost::asio::async_write(socket, boost::asio::buffer(request),
            [this](boost::system::error_code ec, size_t transferred) {
                WriteHandler(ec, transferred);
            });
    }

    void WriteHandler(boost::system::error_code ec, size_t transferred)
    {
        if (ec)
        {
            std::cerr << "Error write to " << host << ": " << ec.message() << std::endl;
            return;
        }
        else if (request.size() != transferred)
        {
            request.erase(0, transferred);
            boost::asio::async_write(socket, boost::asio::buffer(request),
                [this](boost::system::error_code ec, size_t transferred) {
                    WriteHandler(ec, transferred);
                });
        }
        else
        {
            boost::asio::async_read(socket, boost::asio::dynamic_buffer(response),
                [this](boost::system::error_code ec, size_t transferred) {
                    ReadHandler(ec, transferred);
                });
        }
    }

    void ReadHandler(boost::system::error_code ec, size_t transferred)
    {
        if (ec && ec.value() != 2)
        {
            std::cerr << "Error read from " << host << ": " << ec.message() << std::endl;
            return;
        }
    }

    const std::string& GetResponse() const noexcept
    {
        return response;
    }
    
    private:
        boost::asio::ip::tcp::resolver resolver;
        boost::asio::ip::tcp::socket socket;
        std::string request, response;
        const std::string host;
};

int main()
{
    boost::asio::io_context ctx{};
    auto req = Request("www.qq.com", ctx);
    ctx.run();
    std::cout << "Response: \n" << req.GetResponse() << std::endl;
}
