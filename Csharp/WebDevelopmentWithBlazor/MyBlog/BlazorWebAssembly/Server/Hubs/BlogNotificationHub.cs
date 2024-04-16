using Microsoft.AspNetCore.SignalR;
using Data.Models;

namespace BlazorWebAssembly.Server.Hubs
{
    public class BlogNotificationHub : Hub
    {
        public async Task SendNotification(BlogPost post)
        {
            await Clients.All.SendAsync("BlogPostChanged", post);
        }
    }
}
