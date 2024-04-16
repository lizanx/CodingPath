using Microsoft.AspNetCore.Components.Server.ProtectedBrowserStorage;
using Components.Interfaces;

namespace BlazorServer.Services
{
    public class BlogProtectedBrowserStorage : IBrowserStorage
    {
        public BlogProtectedBrowserStorage(ProtectedSessionStorage storage)
        {
            Storage = storage;
        }

        public async Task<T?> GetAsync<T>(string key)
        {
            var value = await Storage.GetAsync<T>(key);
            if (value.Success)
            {
                return value.Value;
            }
            else
            {
                return default;
            }
        }
        public async Task SetAsync(string key, object value)
        {
            await Storage.SetAsync(key, value);
        }
        public async Task DeleteAsync(string key)
        {
            await Storage.DeleteAsync(key);
        }
        ProtectedSessionStorage Storage { get; set; }
    }
}
