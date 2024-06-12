namespace CustomMiddleware;

public class PingPongMiddleware
{
    private readonly RequestDelegate _next;

    public PingPongMiddleware(RequestDelegate next)
    {
        _next = next;
    }

    public async Task Invoke(HttpContext context)
    {
        if (context.Request.Path.StartsWithSegments("/ping"))
        {
            context.Response.ContentType = "text/plain";
            await context.Response.WriteAsync("Hello from PingPongMiddleware class!");
        }
        else
        {
            await _next(context);
        }
    }
}
