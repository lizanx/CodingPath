using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Data.Models;
using Data.Models.Interfaces;

namespace MyBlog.Tests
{
    public class BlogApiMock : IBlogApi
    {
        public async Task<BlogPost?> GetBlogPostAsync(string id)
        {
            BlogPost blogPost = new()
            {
                Id = id,
                Text = $"This is a blog post no {id}",
                PublishDate = DateTime.Now,
                Category = await GetCategoryAsync("1")
            };
            blogPost.Tags.Add(await GetTagAsync("1"));
            blogPost.Tags.Add(await GetTagAsync("2"));
            
            return blogPost;
        }

        public Task<int> GetBlogPostCountAsync()
        { 
            return Task.FromResult(10);
        }

        public async Task<List<BlogPost>?> GetBlogPostsAsync(int numberofposts, int startindex)
        {
            List<BlogPost> posts = new();
            for (int i = 0;i < numberofposts; i++)
            {
                posts.Add(await GetBlogPostAsync($"{startindex + i}"));
            }
            return posts;
        }

        public Task<Category?> GetCategoryAsync(string id)
        {
            return Task.FromResult(new Category() { Id = id, Name = $"Category {id}" });
        }
        public async Task<List<Category>?> GetCategoriesAsync()
        {
            List<Category> categories = new();
            for (int i = 0; i < 10; i++)
            {
                categories.Add(await GetCategoryAsync($"{i}"));
            }
            return categories;
        }

        public Task<Tag?> GetTagAsync(string id)
        {
            return Task.FromResult(new Tag() { Id = id, Name = $"Tag {id}" });
        }
        public async Task<List<Tag>?> GetTagsAsync()
        {
            List<Tag> tags = new();
            for (int i = 0; i < 10; i++)
            {
                tags.Add(await GetTagAsync($"i"));
            }
            return tags;
        }

        public Task InvalidateCacheAsync() => Task.CompletedTask;

        public Task<BlogPost?> SaveBlogPostAsync(BlogPost item) => Task.FromResult(item);
        public Task<Category?> SaveCategoryAsync(Category item) => Task.FromResult(item);
        public Task<Tag?> SaveTagAsync(Tag item) => Task.FromResult(item);

        public Task DeleteBlogPostAsync(string id) => Task.CompletedTask;
        public Task DeleteCategoryAsync(string id) => Task.CompletedTask;
        public Task DeleteTagAsync(string id) => Task.CompletedTask;
    }
}
