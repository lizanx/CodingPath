using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using MyMediaCollection.Enums;
using MyMediaCollection.Model;
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
        private ObservableCollection<MediaItem> items;

        private ObservableCollection<MediaItem> allItems;

        [ObservableProperty]
        [NotifyCanExecuteChangedFor(nameof(DeleteCommand))]
        private MediaItem selectedMediumItem;

        private int additionalItemCount = 1;

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

        public MainViewModel()
        {
            PopulateData();
        }

        private void PopulateData()
        {
            var cd = new MediaItem
            {
                Id = 1,
                Name = "Classical Favorites",
                MediaType = ItemType.Music,
                MediaInfo = new Media { Id = 1, MediaType = ItemType.Music, Name = "CD" }
            };

            var book = new MediaItem
            {
                Id = 2,
                Name = "Classic Fairy Tales",
                MediaType = ItemType.Book,
                MediaInfo = new Media { Id = 2, MediaType = ItemType.Book, Name = "Book" }
            };

            var bluRay = new MediaItem
            {
                Id = 3,
                Name = "The Mummy",
                MediaType = ItemType.Video,
                MediaInfo = new Media { Id = 3, MediaType = ItemType.Video, Name = "Blu Ray" }
            };

            Items = new ObservableCollection<MediaItem>
            {
                cd,
                book,
                bluRay
            };

            allItems = new ObservableCollection<MediaItem>(Items);

            Mediums = new List<string>
            {
                "All",
                nameof(ItemType.Book),
                nameof(ItemType.Music),
                nameof(ItemType.Video)
            };

            SelectedMedium = Mediums[0];
        }

        [RelayCommand]
        private void AddEdit()
        {
            const int startingItemCount = 3;
            var newItem = new MediaItem
            {
                Id = startingItemCount + additionalItemCount,
                Location = LocationType.InCollection,
                MediaType = ItemType.Music,
                MediaInfo = new Media
                {
                    Id = 1,
                    MediaType = ItemType.Music,
                    Name = "CD"
                },
                Name = $"CD {additionalItemCount}"
            };
            allItems.Add(newItem);
            Items.Add(newItem);
            additionalItemCount++;
        }

        [RelayCommand(CanExecute = nameof(CanDeleteItem))]
        private void Delete()
        {
            allItems.Remove(SelectedMediumItem);
            Items.Remove(SelectedMediumItem);
        }

        private bool CanDeleteItem() => SelectedMediumItem != null;
    }
}
