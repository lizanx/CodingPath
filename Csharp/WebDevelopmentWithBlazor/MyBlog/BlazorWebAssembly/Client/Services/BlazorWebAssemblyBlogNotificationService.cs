using Microsoft.AspNetCore.Components;
using Microsoft.AspNetCore.SignalR.Client;
using Data.Models;
using Components.Interfaces;

namespace BlazorWebAssembly.Client.Services
{
    public class BlazorWebAssemblyBlogNotificationService : IBlogNotificationService, IAsyncDisposable
    {
        public BlazorWebAssemblyBlogNotificationService(NavigationManager navigationManager)
        {
            hubConnection = new HubConnectionBuilder()
                .WithUrl(navigationManager.ToAbsoluteUri("/BlogNotificationHub"))
                .Build();
            hubConnection.On<BlogPost>("BlogPostChanged", (post) =>
            {
                BlogPostChanged?.Invoke(post);
            });
            hubConnection.StartAsync();
        }

        public async Task SendNotification(BlogPost post)
        {
            await hubConnection.SendAsync("SendNotification", post);
        }

        public async ValueTask DisposeAsync()
        {
            await hubConnection.DisposeAsync();
        }

        private readonly HubConnection hubConnection;
        public event Action<BlogPost>? BlogPostChanged;
    }
}
