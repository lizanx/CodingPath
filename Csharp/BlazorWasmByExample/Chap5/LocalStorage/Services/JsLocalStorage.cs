using System.Text.Json;
using Microsoft.JSInterop;

namespace LocalStorage.Services;

public class JsLocalStorage : ILocalStorage
{
    private readonly IJSRuntime _js;
    private readonly ILogger<JsLocalStorage> _logger;

    public JsLocalStorage(IJSRuntime jsRuntime, ILogger<JsLocalStorage> logger)
    {
        _logger = logger;
        _js = jsRuntime;
    }

    public async ValueTask<T?> GetItemAsync<T>(string key)
    {
        var jsonStr = await _js.InvokeAsync<string>("storage.getData", key);
        return JsonSerializer.Deserialize<T>(jsonStr);
    }

    public async ValueTask SetItemAsync<T>(string key, T value)
    {
        // _logger.LogInformation("Try to store [{Key}, {Value}]", key, value);
        await _js.InvokeVoidAsync("storage.setData", key, JsonSerializer.Serialize(value));
    }
}
