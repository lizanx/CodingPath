using Microsoft.AspNetCore.Mvc.Testing;
using Microsoft.VisualStudio.TestPlatform.TestHost;

namespace CustomMiddleware.IntegrationTest.WebAppFactory;

public class PingPongMiddlewareTest : IClassFixture<WebApplicationFactory<Program>>
{
    private readonly WebApplicationFactory<Program> _fixture;

    public PingPongMiddlewareTest(WebApplicationFactory<Program> fixture)
    {
        _fixture = fixture;
    }

    [Fact]
    public async Task PingPongMiddleware_ReturnWhenMatch()
    {
        var client = _fixture.CreateClient();

        var response = await client.GetAsync("/ping");

        response.EnsureSuccessStatusCode();
        var content = await response.Content.ReadAsStringAsync();
        Assert.Equal("pong", content);
    }
}
