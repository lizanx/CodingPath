using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.UI.Xaml.Input;
using UnoMediaCollection.Enums;
using UnoMediaCollection.Interfaces;
using UnoMediaCollection.Models;

namespace UnoMediaCollection.ViewModels;

public partial class MainViewModel : ObservableObject
{
    [ObservableProperty]
    private string selectedMedium;
    [ObservableProperty]
    private ObservableCollection<MediaItem> items = new ObservableCollection<MediaItem>();
    private ObservableCollection<MediaItem> allItems;
    [ObservableProperty]
    private ObservableCollection<string> mediums;
    [ObservableProperty]
    [NotifyCanExecuteChangedFor(nameof(DeleteCommand))]
    private MediaItem selectedMediaItem;
    private INavigationService _navigationService;
    private IDataService _dataService;
    private const string AllMediums = "All";

    public MainViewModel(INavigationService navigationService, IDataService dataService)
    {
        _navigationService = navigationService;
        _dataService = dataService;

        PopulateData();
    }

    public void PopulateData()
    {
        Items.Clear();

        foreach (var item in _dataService.GetItems())
        {
            Items.Add(item);
        }

        allItems = new ObservableCollection<MediaItem>(Items);

        Mediums = new ObservableCollection<string>
            {
                AllMediums
            };

        foreach (var itemType in _dataService.GetItemTypes())
        {
            Mediums.Add(itemType.ToString());
        }

        SelectedMedium = Mediums[0];
    }

    partial void OnSelectedMediumChanged(string value)
    {
        Items.Clear();

        foreach (var item in allItems)
        {
            if (string.IsNullOrWhiteSpace(value)
                || value == "All"
                || value == item.MediaType.ToString())
            {
                Items.Add(item);
            }
        }
    }

    [RelayCommand]
    private void AddEdit()
    {
        var selectedItemId = -1;

        if (SelectedMediaItem != null)
        {
            selectedItemId = SelectedMediaItem.Id;
        }

        _navigationService.NavigateTo("ItemDetailsPage", selectedItemId);
    }

    public void ListViewDoubleTapped(object sender, DoubleTappedRoutedEventArgs e)
    {
        AddEdit();
    }

    [RelayCommand(CanExecute = nameof(CanDeleteItem))]
    private void Delete()
    {
        allItems.Remove(SelectedMediaItem);
        Items.Remove(SelectedMediaItem);
    }

    private bool CanDeleteItem() => SelectedMediaItem != null;
}
