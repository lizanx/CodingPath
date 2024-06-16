namespace CustomMiddleware;

public class PingPongMiddleware(RequestDelegate next)
{
    private readonly RequestDelegate _next = next;

    public  async Task Invoke(HttpContext context)
    {
        if (context.Request.Path.StartsWithSegments("/ping"))
        {
            context.Response.ContentType = "text/plain";
            await context.Response.WriteAsync("pong");
            return;
        }

        await _next(context);
    }
}
