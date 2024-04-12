using Microsoft.AspNetCore.Components.WebAssembly.Authentication;
using System.Text.Json;
using System.Net.Http.Json;
using Data.Models;
using Data.Models.Interfaces;

namespace BlazorWebAssembly.Client;
public class BlogApiWebClient : IBlogApi
{
    public BlogApiWebClient(IHttpClientFactory httpClientFactory)
    {
        _factory = httpClientFactory;
    }

    public async Task<BlogPost?> GetBlogPostAsync(string id)
    {
        var client = _factory.CreateClient("Public");
        return await client.GetFromJsonAsync<BlogPost>($"api/BlogPosts/{id}");
    }
    public async Task<int> GetBlogPostCountAsync()
    {
        var client = _factory.CreateClient("Public");
        return await client.GetFromJsonAsync<int>("api/BlogPostCount");
    }
    public async Task<List<BlogPost>?> GetBlogPostsAsync(int numberOfPosts, int startIndex)
    {
        var client = _factory.CreateClient("Public");
        return await client.GetFromJsonAsync<List<BlogPost>>($"api/BlogPosts?numberofposts={numberOfPosts}&startindex={startIndex}");
    }
    public async Task<BlogPost?> SaveBlogPostAsync(BlogPost item)
    {
        try
        {
            var client = _factory.CreateClient("Authenticated");
            var response = await client.PutAsJsonAsync<BlogPost>("api/BlogPosts", item);
            var json = await response.Content.ReadAsStringAsync();
            return JsonSerializer.Deserialize<BlogPost>(json);
        }
        catch (AccessTokenNotAvailableException ex)
        {
            ex.Redirect();
        }
        return null;
    }
    public async Task DeleteBlogPostAsync(string id)
    {
        try
        {
            var client = _factory.CreateClient("Authenticated");
            await client.DeleteAsync($"api/BlogPosts/{id}");
        }
        catch (AccessTokenNotAvailableException ex)
        {
            ex.Redirect();
        }
    }

    public async Task<List<Category>?> GetCategoriesAsync()
    {
        var client = _factory.CreateClient("Public");
        return await client.GetFromJsonAsync<List<Category>>("api/Categories");
    }
    public async Task<Category?> GetCategoryAsync(string id)
    {
        var client = _factory.CreateClient("Public");
        return await client.GetFromJsonAsync<Category>($"api/Categories/{id}");
    }
    public async Task DeleteCategoryAsync(string id)
    {
        try
        {
            var client = _factory.CreateClient("Authenticated");
            await client.DeleteAsync($"api/Categories/{id}");
        }
        catch (AccessTokenNotAvailableException ex)
        {
            ex.Redirect();
        }
    }
    public async Task<Category?> SaveCategoryAsync(Category item)
    {
        try
        {
            var client = _factory.CreateClient("Authenticated");
            var response = await client.PutAsJsonAsync<Category>("api/Categories", item);
            var json = await response.Content.ReadAsStringAsync();
            return JsonSerializer.Deserialize<Category>(json);
        }
        catch (AccessTokenNotAvailableException ex)
        {
            ex.Redirect();
        }
        return null;
    }

    public async Task<Tag?> GetTagAsync(string id)
    {
        var client = _factory.CreateClient("Public");
        return await client.GetFromJsonAsync<Tag>($"api/Tags/{id}");
    }
    public async Task<List<Tag>?> GetTagsAsync()
    {
        var client = _factory.CreateClient("Public");
        return await client.GetFromJsonAsync<List<Tag>>("api/Tags");
    }
    public async Task DeleteTagAsync(string id)
    {
        try
        {
            var client = _factory.CreateClient("Authenticated");
            await client.DeleteAsync($"api/Tags/{id}");
        }
        catch (AccessTokenNotAvailableException ex)
        {
            ex.Redirect();
        }
    }
    public async Task<Tag?> SaveTagAsync(Tag item)
    {
        try
        {
            var client = _factory.CreateClient("Authenticated");
            var response = await client.PutAsJsonAsync<Tag>("api/Tags", item);
            var json = await response.Content.ReadAsStringAsync();
            return JsonSerializer.Deserialize<Tag>(json);
        }
        catch (AccessTokenNotAvailableException ex)
        {
            ex.Redirect();
        }
        return null;
    }

    public Task InvalidateCacheAsync()
    {
        throw new NotImplementedException();
    }

    private readonly IHttpClientFactory _factory;
}
