using Microsoft.AspNetCore.Http;

namespace CustomMiddleware.Test;

public class PingPongMiddlewareTest
{
    [Fact]
    public async Task PingPong_PassWhenMismatch()
    {
        bool restOfPipelineExecuted = false;
        RequestDelegate restOfPipeline = (context) => {
            restOfPipelineExecuted = true;
            return Task.CompletedTask;
        };
        var middleware = new PingPongMiddleware(restOfPipeline);
        var context = new DefaultHttpContext();
        context.Request.Path = "/NotPing";

        await middleware.Invoke(context);

        Assert.True(restOfPipelineExecuted);
    }

    [Fact]
    public async Task PingPong_ReturnWhenMatch()
    {
        RequestDelegate restOfPipeline = (context) => throw new Exception("Shouldn't reach here!");
        var context = new DefaultHttpContext();
        context.Request.Path = "/ping";
        context.Response.Body = new MemoryStream();
        var middleware = new PingPongMiddleware(restOfPipeline);

        await middleware.Invoke(context);
        string response;
        context.Response.Body.Seek(0, SeekOrigin.Begin);
        using (var responseReader= new StreamReader(context.Response.Body))
        {
            response = await responseReader.ReadToEndAsync();
        }

        Assert.Equal("pong", response);
        Assert.Equal("text/plain", context.Response.ContentType);
        Assert.Equal(200, context.Response.StatusCode);
    }
}