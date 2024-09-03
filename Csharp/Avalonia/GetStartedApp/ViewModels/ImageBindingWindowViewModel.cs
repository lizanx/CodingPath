using System;
using System.Threading.Tasks;
using Avalonia.Media.Imaging;
using CommunityToolkit.Mvvm.ComponentModel;
using GetStartedApp.Helpers;

namespace GetStartedApp.ViewModels;

public partial class ImageBindingWindowViewModel : ObservableObject
{
    [ObservableProperty] private Bitmap? _imageFromResource =
        ImageHelper.LoadFromResource(new Uri("avares://GetStartedApp/Assets/Girls.PNG"));

    [ObservableProperty] private Task<Bitmap?> _imageFromWeb =
        ImageHelper.LoadFromWebAsync(new Uri("https://wallpapercave.com/wp/wp7579925.jpg"));
}