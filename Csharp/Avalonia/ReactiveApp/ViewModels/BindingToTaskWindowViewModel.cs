using System.Threading.Tasks;

namespace ReactiveApp.ViewModels;

public class BindingToTaskWindowViewModel
{
    public Task<string> MyAsyncText => GetTextAsync();

    private async Task<string> GetTextAsync()
    {
        await Task.Delay(5 * 1000);
        return "Text content after 5 seconds";
    }
}