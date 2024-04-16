using Data.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Components.Interfaces
{
    public interface IBlogNotificationService
    {
        event Action<BlogPost>? BlogPostChanged;
        Task SendNotification(BlogPost blogPost);
    }
}
