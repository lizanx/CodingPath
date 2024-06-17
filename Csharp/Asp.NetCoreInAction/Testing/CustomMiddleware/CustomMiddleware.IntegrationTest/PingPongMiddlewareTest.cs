using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.TestHost;
using Microsoft.Extensions.Hosting;

namespace CustomMiddleware.IntegrationTest;

public class PingPongMiddlewareTest
{
    [Fact]
    public async void PingPongMiddleware_ReturnWhenMatch()
    {
        var hostBuilder = new HostBuilder()
            .ConfigureWebHost(webHost =>
            {
                webHost.Configure(app =>
                {
                    app.UseMiddleware<PingPongMiddleware>();
                });
                webHost.UseTestServer();
            });
        IHost host = await hostBuilder.StartAsync();
        var client = host.GetTestClient();

        var response = await client.GetAsync("/ping");
        
        response.EnsureSuccessStatusCode();
        var content = await response.Content.ReadAsStringAsync();
        Assert.Equal("pong", content);
    }
}