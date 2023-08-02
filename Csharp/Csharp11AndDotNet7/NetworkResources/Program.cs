using System.Net;
using System.Net.NetworkInformation;

string url = "https://stackoverflow.com/search?q=securestring";
Uri uri = new(url);
WriteLine($"URL: {url}");
WriteLine($"Scheme: {uri.Scheme}");
WriteLine($"Port: {uri.Port}");
WriteLine($"Host: {uri.Host}");
WriteLine($"Path: {uri.AbsolutePath}");
WriteLine($"Query: {uri.Query}");

IPHostEntry entry = Dns.GetHostEntry(uri.Host);
WriteLine($"Hostname {entry.HostName} has following IP addresses:");
foreach (IPAddress addr in entry.AddressList)
{
    WriteLine($"{addr} ({addr.AddressFamily})");
}

try
{
    Ping ping = new();
    PingReply reply = ping.Send(uri.Host);
    WriteLine($"{uri.Host} was pinged and replied {reply.Status}");

    if (reply.Status == IPStatus.Success)
    {
        WriteLine($"Reply from {reply.Address} took {reply.RoundtripTime}ms");
    }
}
catch (Exception ex)
{
    WriteLine($"{ex.GetType()} says {ex.Message}");
}

string city = "Aberdeen";
ReadOnlySpan<char> citySpan = city.AsSpan()[^5..^0];
WriteLine(citySpan.ToString());