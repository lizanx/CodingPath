using System;
using System.Net.Http;
using System.Threading.Tasks;
using Avalonia.Media.Imaging;
using Avalonia.Platform;

namespace GetStartedApp.Helpers;

public static class ImageHelper
{
    private static readonly HttpClient HttpClient = new HttpClient();

    public static Bitmap LoadFromResource(Uri resourceUri)
    {
        return new Bitmap(AssetLoader.Open(resourceUri));
    }

    public static async Task<Bitmap?> LoadFromWebAsync(Uri url)
    {
        try
        {
            var response = await HttpClient.GetAsync(url);
            response.EnsureSuccessStatusCode();
            var data = await response.Content.ReadAsStreamAsync();
            return new Bitmap(data);
        }
        catch (HttpRequestException ex)
        {
            Console.WriteLine($"An error occurred when downloading from {url}: {ex.Message}");
            return null;
        }
    }
}