using Components.Interfaces;
using Data.Models;

namespace BlazorServer.Services
{
    public class BlazorServerBlogNotificationService : IBlogNotificationService
    {
        public event Action<BlogPost>? BlogPostChanged;
        public Task SendNotification(BlogPost blogPost)
        {
            BlogPostChanged?.Invoke(blogPost);
            return Task.CompletedTask;
        }
    }
}
