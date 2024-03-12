#include <string>
#include <iostream>
#include <sstream>
#include <boost/asio.hpp>

std::vector<std::string> request(std::string host, const std::vector<std::string>& resources, boost::asio::io_context &ctx)
{
    std::vector<std::string> responses{};

    std::stringstream requestStream{};
    for (const auto& resource : resources)
    {
        requestStream.str("");
        requestStream << "GET " << resource << " HTTP/1.1\r\n"
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

        responses.push_back(std::move(response));
    }
    return responses;
}

int main()
{
    std::vector<std::string> reqResources{
        "/questions/11227809/why-is-processing-a-sorted-array-faster-than-processing-an-unsorted-array",
        "/questions/927358/how-do-i-undo-the-most-recent-local-commits-in-git",
        "/questions/2003505/how-do-i-delete-a-git-branch-locally-and-remotely"
    };
    boost::asio::io_context ctx{};
    try
    {
        const auto results = request("www.stackoverflow.com", reqResources, ctx);
        for (size_t i{}; i < reqResources.size(); i++)
        {
            std::cout << "Requested resource: " << reqResources[i] << "\n"
                    << "Response: \n" << results[i] << "\n-----\n";
        }
    }
    catch(const boost::system::system_error& se)
    {
        std::cerr << "Error: " << se.what() << '\n';
    }
}
