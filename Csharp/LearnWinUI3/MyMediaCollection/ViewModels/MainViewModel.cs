﻿using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using Microsoft.UI.Xaml.Input;
using MyMediaCollection.Enums;
using MyMediaCollection.Interfaces;
using MyMediaCollection.Model;
using MyMediaCollection.Views;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace MyMediaCollection.ViewModels
{
    public partial class MainViewModel : ObservableObject
    {
        [ObservableProperty]
        private string selectedMedium;

        [ObservableProperty]
        private IList<string> mediums;

        [ObservableProperty]
        private ObservableCollection<MediaItem> items = [];

        private ObservableCollection<MediaItem> allItems;

        [ObservableProperty]
        [NotifyCanExecuteChangedFor(nameof(DeleteCommand))]
        private MediaItem selectedMediumItem;

        private const string AllMediums = "All";

        private readonly INavigationService _navigationService;
        private readonly IDataService _dataService;

        partial void OnSelectedMediumChanged(string value)
        {
            Items.Clear();
            foreach (var item in allItems)
            {
                if (string.IsNullOrWhiteSpace(SelectedMedium)
                    || SelectedMedium == "All"
                    || value == item.MediaType.ToString())
                {
                    Items.Add(item);
                }
            }
        }

        public MainViewModel(INavigationService navigationService, IDataService dataService)
        {
            _navigationService = navigationService;
            _dataService = dataService;
            PopulateData();
        }

        private void PopulateData()
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

        [RelayCommand]
        private void AddEdit()
        {
            var selectedItemId = -1;
            if (SelectedMediumItem is not null)
            {
                selectedItemId = SelectedMediumItem.Id;
            }

            _navigationService.NavigateTo(nameof(ItemDetailsPage), selectedItemId);
        }

        [RelayCommand(CanExecute = nameof(CanDeleteItem))]
        private void Delete()
        {
            allItems.Remove(SelectedMediumItem);
            Items.Remove(SelectedMediumItem);
        }

        private bool CanDeleteItem() => SelectedMediumItem != null;

        public void ListViewDoubleTapped(object sender, DoubleTappedRoutedEventArgs e)
        {
            AddEdit();
        }
    }
}