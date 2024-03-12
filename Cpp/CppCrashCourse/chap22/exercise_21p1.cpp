#include <iostream>
#include <string>
#include <memory>
#include <atomic>
#include <cstdlib>
#include <boost/asio.hpp>
#include <boost/algorithm/string/case_conv.hpp>

using namespace boost::asio;

struct Session : std::enable_shared_from_this<Session>
{
    explicit Session(ip::tcp::socket socket) : socket{ std::move(socket) } {}

    void read()
    {
        async_read_until(socket, dynamic_buffer(message), "\n",
            [self=shared_from_this()](boost::system::error_code ec, std::size_t length) {
                if (ec || self->message == "\n")
                    return;
                boost::algorithm::to_upper(self->message);
                self->write();
            });
    }

    void write()
    {
        async_write(socket, buffer(message),
            [self=shared_from_this()](boost::system::error_code ec, std::size_t length) {
                if (ec)
                    return;
                self->message.clear();
                self->read();
            });
    }
private:
    ip::tcp::socket socket;
    std::string message;
};

static std::atomic_bool keyInterrupt{};

void handler(int signal)
{
    std::cout << "Signal " << signal << " received.\n";
    if (signal == SIGINT)
    {
        keyInterrupt = true;
        std::cout << "SIGINT: won't serve any more connections." << std::endl;
    }
}

void serve(ip::tcp::acceptor& acceptor)
{
    acceptor.async_accept([&acceptor](boost::system::error_code ec, ip::tcp::socket socket) {
        if (keyInterrupt)
        {
            std::cout << "Key interrupt occurred, exit." << std::endl;
            return;
        }

        serve(acceptor);
        if (ec)
            return;
        auto session = std::make_shared<Session>(std::move(socket));
        session->read();
    });
}

int main()
{
    std::signal(SIGINT, handler);
    try
    {
        io_context ctx{};
        ip::tcp::acceptor acceptor{ ctx, ip::tcp::endpoint(ip::tcp::v4(), 1895) };
        serve(acceptor);
        ctx.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}
