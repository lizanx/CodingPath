using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Controls.Primitives;
using Microsoft.UI.Xaml.Data;
using Microsoft.UI.Xaml.Input;
using Microsoft.UI.Xaml.Media;
using Microsoft.UI.Xaml.Navigation;
using MyMediaCollection.Model;
using MyMediaCollection.Enums;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace MyMediaCollection
{
    /// <summary>
    /// An empty window that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainWindow : Window
    {
        private bool _isLoaded;
        private IList<MediaItem> _items { get; set; }
        private IList<MediaItem> _allItems { get; set; }
        private IList<string> _mediums { get; set; }

        public MainWindow()
        {
            this.InitializeComponent();
            ItemList.Loaded += ItemList_Loaded;
            ItemFilter.Loaded += ItemFilter_Loaded;
        }

        private void PopulateData()
        {
            if (_isLoaded) return;
            _isLoaded = true;

            MediaItem cd = new() {
                Id = 1,
                Name = "Classical Favorites",
                MediaType = ItemType.Music,
                MediaInfo = new() {
                    Id = 1,
                    MediaType = ItemType.Music,
                    Name = "CD"
                }
            };
            MediaItem book = new() {
                Id = 2,
                Name = "Classic Fairy Tales",
                MediaType = ItemType.Book,
                MediaInfo = new() {
                    Id = 2,
                    MediaType = ItemType.Book,
                    Name = "Book"
                }
            };
            MediaItem bluRay = new()
            {
                Id = 3,
                Name = "The Mummy",
                MediaType = ItemType.Video,
                MediaInfo = new()
                {
                    Id = 3,
                    MediaType = ItemType.Video,
                    Name = "Blu Ray"
                }
            };

            _items = [cd, book, bluRay];
            _allItems = [cd, book, bluRay];


            _mediums =
            [
                "All",
                nameof(ItemType.Book),
                nameof(ItemType.Music),
                nameof(ItemType.Video),
            ];
        }

        private void ItemList_Loaded(object sender, RoutedEventArgs args)
        {
            var listView = (ListView)sender;
            PopulateData();
            listView.ItemsSource = _items;
        }

        private void ItemFilter_Loaded(object sender, RoutedEventArgs args)
        {
            var filterCombo = (ComboBox)sender;
            PopulateData();
            filterCombo.ItemsSource = _mediums;
            filterCombo.SelectedIndex = 0;

            ItemFilter.SelectionChanged += ItemFilter_SelectionChanged;
        }

        private void ItemFilter_SelectionChanged(object sender, SelectionChangedEventArgs args)
        {
            var updatedItems = _allItems.Where(item =>
                string.IsNullOrWhiteSpace(ItemFilter.SelectedValue.ToString())
                || ItemFilter.SelectedValue.ToString() == "All"
                || item.MediaType.ToString() == ItemFilter.SelectedValue.ToString())
                .ToList();
            ItemList.ItemsSource = updatedItems;
        }

        private async void AddButton_Click(object sender, RoutedEventArgs e)
        {
            var dialog = new ContentDialog
            {
                Title = "My Media Collection",
                Content = "Adding items to the collection is not yet supported",
                CloseButtonText = "OK",
                XamlRoot = Content.XamlRoot
            };
            await dialog.ShowAsync();
        }
    }
}
