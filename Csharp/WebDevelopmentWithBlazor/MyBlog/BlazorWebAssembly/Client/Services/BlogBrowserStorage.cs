using Blazored.SessionStorage;
using Components.Interfaces;

namespace BlazorWebAssembly.Client.Services
{
    public class BlogBrowserStorage : IBrowserStorage
    {
        public BlogBrowserStorage(ISessionStorageService storage)
        {
            Storage = storage;
        }

        public async Task<T?> GetAsync<T>(string key)
        {
            return await Storage.GetItemAsync<T>(key);
        }
        public async Task SetAsync(string key, object value)
        {
            await Storage.SetItemAsync(key, value);
        }
        public async Task DeleteAsync(string key)
        {
            await Storage.RemoveItemAsync(key);
        }

        ISessionStorageService Storage { get; set; }
    }
}
