using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.Json;
using Microsoft.Extensions.Options;
using Data.Models;
using Data.Models.Interfaces;

namespace Data
{
    public class BlogApiJsonDirectAccess: IBlogApi
    {
        public BlogApiJsonDirectAccess(IOptions<BlogApiJsonDirectAccessSetting> option)
        {
            _settings = option.Value;

            //Console.WriteLine($"Data path: {Path.GetFullPath(_settings.DataPath)}");

            if (!Directory.Exists(_settings.DataPath))
            {
                Directory.CreateDirectory(_settings.DataPath);
            }
            var blogPostsPath = $@"{_settings.DataPath}{Path.DirectorySeparatorChar}{_settings.BlogPostsFolder}";
            if (!Directory.Exists(blogPostsPath))
            {
                Directory.CreateDirectory(blogPostsPath);
            }
            var categoriesPath = $@"{_settings.DataPath}{Path.DirectorySeparatorChar}{_settings.CategoriesFolder}";
            if (!Directory.Exists(categoriesPath))
            {
                Directory.CreateDirectory(categoriesPath);
            }
            var tagsPath = $@"{_settings.DataPath}{Path.DirectorySeparatorChar}{_settings.TagsFolder}";
            if (!Directory.Exists(tagsPath))
            {
                Directory.CreateDirectory(tagsPath);
            }
        }

        private void Load<T>(ref List<T>? list, string folder)
        {
            if (list == null)
            {
                list = new List<T>();
                string fullPath = $@"{_settings.DataPath}{Path.DirectorySeparatorChar}{folder}";
                foreach (var file in Directory.GetFiles(fullPath))
                {
                    string jsonContent = File.ReadAllText(file);
                    var deserializedItem = JsonSerializer.Deserialize<T>(jsonContent);
                    if (deserializedItem != null)
                    {
                        list.Add(deserializedItem);
                    }
                }
            }
        }

        private Task LoadBlogPostsAsync()
        {
            Load<BlogPost>(ref _blogPosts, _settings.BlogPostsFolder);
            return Task.CompletedTask;
        }

        private Task LoadCategoriesAsync()
        {
            Load<Category>(ref _categories, _settings.CategoriesFolder);
            return Task.CompletedTask;
        }

        private Task LoadTagsAsync()
        {
            Load<Tag>(ref _tags, _settings.TagsFolder);
            return Task.CompletedTask;
        }

        private async Task SaveAsync<T>(List<T>? list, string folder, string filename, T item)
        {
            string filepath = $@"{_settings.DataPath}{Path.DirectorySeparatorChar}{folder}{Path.DirectorySeparatorChar}{filename}";
            await File.WriteAllTextAsync(filepath, JsonSerializer.Serialize<T>(item));

            list ??= new();
            if (!list.Contains(item))
            {
                list.Add(item);
            }
        }

        private void DeleteAsync<T>(List<T>? list, string folder, string id)
        {
            string filepath = $@"{_settings.DataPath}{Path.DirectorySeparatorChar}{folder}{Path.DirectorySeparatorChar}{id}.json";

            try
            {
                File.Delete(filepath);
            }
            catch
            {
                Console.WriteLine("Failed to delete file {0}", filepath);
            }
        }

        public async Task<int> GetBlogPostCountAsync()
        {
            await LoadBlogPostsAsync();
            if (_blogPosts != null)
            {
                return _blogPosts.Count;
            }
            return 0;
        }

        public async Task<List<BlogPost>?> GetBlogPostsAsync(int numberOfPosts, int startIndex)
        {
            await LoadBlogPostsAsync();
            return _blogPosts ?? new();
        }

        public async Task<BlogPost?> GetBlogPostAsync(string id)
        {
            await LoadBlogPostsAsync();

            if (_blogPosts == null)
                throw new Exception($"Blog post of id '{id}' not found.");
            return _blogPosts.FirstOrDefault(blogPost => blogPost.Id == id);
        }

        public async Task<List<Category>?> GetCategoriesAsync()
        {
            await LoadCategoriesAsync();
            return _categories ?? new();
        }

        public async Task<Category?> GetCategoryAsync(string id)
        {
            await LoadCategoriesAsync();

            if (_categories == null)
                throw new Exception($"Category of id '{id}' not found");
            return _categories.FirstOrDefault(category => category.Id == id);
        }

        public async Task<List<Tag>?> GetTagsAsync()
        {
            await LoadTagsAsync();

            return _tags ?? new();
        }

        public async Task<Tag?> GetTagAsync(string id)
        {
            await LoadTagsAsync();

            if (_tags == null)
                throw new Exception($"Tag of id '{id}' not found");
            return _tags.FirstOrDefault(tag => tag.Id == id);
        }

        public async Task<BlogPost?> SaveBlogPostAsync(BlogPost item)
        {
            item.Id ??= Guid.NewGuid().ToString();

            await SaveAsync<BlogPost>(_blogPosts, _settings.BlogPostsFolder, $"{item.Id}.json", item);
            return item;
        }

        public async Task<Category?> SaveCategoryAsync(Category item)
        {
            item.Id ??= Guid.NewGuid().ToString();

            await SaveAsync<Category>(_categories, _settings.CategoriesFolder, $"{item.Id}.json", item);
            return item;
        }

        public async Task<Tag?> SaveTagAsync(Tag item)
        {
            item.Id ??= Guid.NewGuid().ToString();

            await SaveAsync<Tag>(_tags, _settings.TagsFolder, $"{item.Id}.json", item);
            return item;
        }

        public Task DeleteBlogPostAsync(string id)
        {
            DeleteAsync<BlogPost>(_blogPosts, _settings.BlogPostsFolder, id);
            
            if (_blogPosts != null)
            {
                var item = _blogPosts.FirstOrDefault(blog => blog.Id == id);
                if (item != null)
                    _blogPosts.Remove(item);
            }
            return Task.CompletedTask;
        }

        public Task DeleteCategoryAsync(string id)
        {
            DeleteAsync<Category>(_categories, _settings.CategoriesFolder, id);

            if (_categories != null)
            {
                var item = _categories.FirstOrDefault(category => category.Id == id);
                if (item != null)
                    _categories.Remove(item);
            }
            return Task.CompletedTask;
        }

        public Task DeleteTagAsync(string id)
        {
            DeleteAsync<Tag>(_tags, _settings.TagsFolder, id);

            if (_tags != null)
            {
                var item = _tags.FirstOrDefault(tag => tag.Id == id);
                if (item != null)
                    _tags.Remove(item);
            }
            return Task.CompletedTask;
        }

        public Task InvalidateCacheAsync()
        {
            _blogPosts = null;
            _categories = null;
            _tags = null;
            return Task.CompletedTask;
        }

        private readonly BlogApiJsonDirectAccessSetting _settings;
        private List<BlogPost>? _blogPosts;
        private List<Category>? _categories;
        private List<Tag>? _tags;
    }
}
