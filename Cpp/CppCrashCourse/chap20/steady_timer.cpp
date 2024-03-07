#include <iostream>
#include <chrono>
#include <boost/asio.hpp>

boost::asio::steady_timer make_timer(boost::asio::io_context& io_context)
{
    return boost::asio::steady_timer{
        io_context,
        std::chrono::steady_clock::now() + std::chrono::seconds{ 3 }
    };
}

int main(void)
{
    boost::asio::io_context io_ctx{};

    auto timer = make_timer(io_ctx);
    std::cout << "Enter steady_timer::wait\n";
    timer.wait();
    std::cout << "Exit steady_timer::wait\n";

    timer = make_timer(io_ctx);
    std::cout << "Enter steady_timer::async_wait\n";
    timer.async_wait([](const boost::system::error_code& err) {
        if (!err)
        {
            std::cout << "<<callback function>>\n";
        }
    });
    std::cout << "Exit steady_timer::async_wait\n";

    io_ctx.run();
    std::cout << "Exit io_context::run\n";
}