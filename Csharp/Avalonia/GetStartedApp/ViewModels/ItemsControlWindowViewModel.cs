using System.Collections.ObjectModel;
using CommunityToolkit.Mvvm.ComponentModel;

namespace GetStartedApp.ViewModels;

public partial class ItemsControlWindowViewModel : ObservableObject
{
    [ObservableProperty]
    private ObservableCollection<Tile> _tiles;

    public ItemsControlWindowViewModel()
    {
        _tiles =
        [
            new Tile(10, 10, 10),
            new Tile(10, 20, 20),
            new Tile(10, 30, 30),
        ];
    }
}

public record Tile(int Size, int TopX, int TopY);
