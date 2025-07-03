using System.Buffers;
using System.Net;
using System.Net.Security;
using System.Net.Sockets;
using System.Text;

IPAddress[] iPAddresses = await Dns.GetHostAddressesAsync("www.baidu.com");

var buffer = ArrayPool<byte>.Shared.Rent(1024 * 1024);
if (buffer is null)
{
    Console.WriteLine("Error: failed to rent buffer from memory pool!");
    return;
}

Console.WriteLine(">>> Start HTTP request <<<");
try
{
    foreach (var ipAddr in iPAddresses)
    {
        if (ipAddr.AddressFamily != AddressFamily.InterNetwork)
        {
            Console.WriteLine("Not IPv4 address, skip {0}", ipAddr);
            continue;
        }

        Console.WriteLine("Connecting to IP {0}", ipAddr);

        using var socket = new Socket(SocketType.Stream, ProtocolType.Tcp);
        if (socket is null)
        {
            Console.WriteLine("Error: failed to create socket.");
            continue;
        }

        await socket.ConnectAsync(ipAddr, 80);

        using var networkStream = new NetworkStream(socket);
        if (networkStream is null)
        {
            Console.WriteLine("Failed to create network stream.");
            continue;
        }

        Console.WriteLine("Connected, sending request..");

        string content = """
                        GET https://www.baidu.com HTTP/1.1
                        Host: www.baidu.com


                        """;
        var contentBytes = Encoding.UTF8.GetBytes(content);
        if (contentBytes is null)
        {
            Console.WriteLine("Error: failed to convert content into bytes.");
            continue;
        }
        contentBytes.CopyTo(buffer.AsMemory());
        ReadOnlyMemory<byte> writeBuffer = buffer.AsMemory(0, contentBytes.Length);
        await networkStream.WriteAsync(writeBuffer);

        Console.WriteLine("Request sent, getting response...");
        var length = await networkStream.ReadAsync(buffer);
        string response = Encoding.UTF8.GetString(buffer, 0, length);
        Console.WriteLine("Response: {0}\n", response[..50]);
    }
}
catch (Exception e)
{
    Console.WriteLine($"Error occurred: {e}");
}
finally
{
    ArrayPool<byte>.Shared.Return(buffer);
}

Console.WriteLine("\n>>> Start HTTPS request <<<");
try
{
    foreach (var ipAddr in iPAddresses)
    {
        if (ipAddr.AddressFamily != AddressFamily.InterNetwork)
        {
            Console.WriteLine("Not IPv4 address, skip {0}", ipAddr);
            continue;
        }

        Console.WriteLine("Connecting to IP {0}", ipAddr);

        using var socket = new Socket(SocketType.Stream, ProtocolType.Tcp);
        if (socket is null)
        {
            Console.WriteLine("Error: failed to create socket.");
            continue;
        }

        await socket.ConnectAsync(ipAddr, 443);

        using var networkStream = new NetworkStream(socket);
        if (networkStream is null)
        {
            Console.WriteLine("Failed to create network stream.");
            continue;
        }
        using var sslStream = new SslStream(networkStream);
        if (sslStream is null)
        {
            Console.WriteLine("Failed to create ssl stream.");
            continue;
        }
        await sslStream.AuthenticateAsClientAsync("www.baidu.com");

        Console.WriteLine("Connected, sending request..");

        string content = """
                        GET https://www.baidu.com HTTP/1.1
                        Host: www.baidu.com


                        """;
        var contentBytes = Encoding.UTF8.GetBytes(content);
        if (contentBytes is null)
        {
            Console.WriteLine("Error: failed to convert content into bytes.");
            continue;
        }
        contentBytes.CopyTo(buffer.AsMemory());
        ReadOnlyMemory<byte> writeBuffer = buffer.AsMemory(0, contentBytes.Length);
        await sslStream.WriteAsync(writeBuffer);

        Console.WriteLine("Request sent, getting response...");
        var length = await sslStream.ReadAsync(buffer);
        string response = Encoding.UTF8.GetString(buffer, 0, length);
        Console.WriteLine("Response: {0}\n", response[..50]);
    }
}
catch (Exception e)
{
    Console.WriteLine($"Error occurred: {e}");
}
finally
{
    ArrayPool<byte>.Shared.Return(buffer);
}
