namespace CustomMiddleware;

public static class MiddlewareExtensions
{
    public static IApplicationBuilder UsePingPong(this IApplicationBuilder app)
    {
        app.UseMiddleware<PingPongMiddleware>();
        return app;
    }
}
