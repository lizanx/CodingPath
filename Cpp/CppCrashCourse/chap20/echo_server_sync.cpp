#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/algorithm/string/case_conv.hpp>

using namespace boost::asio;

void handle(ip::tcp::socket& socket)
{
    boost::system::error_code ec{};
    std::string message{};

    do
    {
        read_until(socket, dynamic_buffer(message), "\n");
        boost::algorithm::to_upper(message);
        write(socket, buffer(message), ec);
        if (message == "\n")
        {
            return;
        }
        message.clear();
    } while (!ec);
}

int main()
{
    try
    {
        io_context ctx{};
        ip::tcp::acceptor acceptor{ ctx, ip::tcp::endpoint(ip::tcp::v4(), 1895) };

        while (true)
        {
            ip::tcp::socket socket{ ctx };
            acceptor.accept(socket);
            handle(socket);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}