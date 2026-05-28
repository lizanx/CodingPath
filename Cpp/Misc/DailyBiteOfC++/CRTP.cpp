#include <chrono>
#include <print>
#include <span>
#include <thread>
#include <vector>

namespace
{
    struct Connection
    {
    };

    struct ServerConfig
    {
    };

    template <typename THandler>
    class SimpleServer
    {
    public:
        void Listen()
        {
            bool running = true;
            while (running)
            {
                Connection conn = AcceptConnection();
                // Safe, because we know that THandler is a derived class.
                static_cast<THandler *>(this)->HandleConnection(conn);
            }
        }

    protected:
        SimpleServer(ServerConfig config)
        {
        }

        int Read(Connection conn, std::span<std::byte> buf)
        {
            std::println("SimpleServer::Read -> buffer size = {}", buf.size());
            return buf.size();
        }

        int Write(Connection conn, std::span<std::byte> buf)
        {
            std::println("SimpleServer::Write -> buffer size = {}", buf.size());
            return buf.size();
        }

    private:
        Connection AcceptConnection()
        {
            std::println("SimpleServer::AcceptConnection");
            return {};
        }
    };

    class ServerImpl : public SimpleServer<ServerImpl>
    {
    public:
        ServerImpl(ServerConfig config) : SimpleServer{config} {}

        void HandleConnection(Connection conn)
        {
            std::println("ServerImpl::HandleConnection");
            std::vector<std::byte> buffer(64 * 1024);

            int readCnt = Read(conn, buffer);
            std::this_thread::sleep_for(std::chrono::seconds{2});
            int writeCnt = Write(conn, buffer);

            std::println("Read {} bytes, write {} bytes", readCnt, writeCnt);
        }
    };
}

int main()
{
    ServerImpl server{ServerConfig{}};
    server.Listen();

    return 0;
}
