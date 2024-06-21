namespace LocalStorage.Services;

public interface ILocalStorage
{
    ValueTask<T?> GetItemAsync<T>(string key);
    ValueTask SetItemAsync<T>(string key, T value);
}
