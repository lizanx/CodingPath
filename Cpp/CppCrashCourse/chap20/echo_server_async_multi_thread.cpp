#include <iostream>
#include <string>
#include <memory>
#include <future>
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

void serve(ip::tcp::acceptor& acceptor)
{
    acceptor.async_accept([&acceptor](boost::system::error_code ec, ip::tcp::socket socket) {
        serve(acceptor);
        if (ec)
            return;
        auto session = std::make_shared<Session>(std::move(socket));
        session->read();
    });
}

int main()
{
    const int nThreads{ 4 };
    io_context ctx{ nThreads };
    ip::tcp::acceptor acceptor{ ctx, ip::tcp::endpoint(ip::tcp::v4(), 1895) };
    serve(acceptor);
    
    std::vector<std::future<void>> futures{};
    std::generate_n(std::back_inserter(futures), nThreads,
        [&ctx] {
            return std::async(std::launch::async, [&ctx] { ctx.run(); });
        });
    
    for (auto& future : futures)
    {
        try
        {
            future.get();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}
