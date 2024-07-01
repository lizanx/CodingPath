using MyMediaCollection.Enums;
using MyMediaCollection.Model;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MyMediaCollection.ViewModels
{
    public class MainViewModel : BindableBase
    {
        private string selectedMedium;
        private IList<string> mediums;
        private ObservableCollection<MediaItem> items;
        private ObservableCollection<MediaItem> allItems;
        private MediaItem selecteMediumItem;
        private int additionalItemCount = 1;

        public ObservableCollection<MediaItem> Items
        {
            get { return items; }
            set { SetProperty(ref items, value); }
        }

        public IList<string> Mediums
        {
            get { return mediums; }
            set { SetProperty(ref mediums, value); }
        }

        public string SelectedMedium
        {
            get => selectedMedium;
            set
            {
                SetProperty(ref selectedMedium, value);
                Items.Clear();
                foreach (var item in allItems)
                {
                    if (string.IsNullOrWhiteSpace(selectedMedium)
                        || selectedMedium == "All"
                        || selectedMedium == item.MediaType.ToString())
                    {
                        Items.Add(item);
                    }
                }
            }
        }

        public MediaItem SelectedMediaItem
        {
            get => selecteMediumItem;
            set
            {
                SetProperty(ref selecteMediumItem, value);
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

            items = new ObservableCollection<MediaItem>
            {
                cd,
                book,
                bluRay
            };

            allItems = new ObservableCollection<MediaItem>(Items);

            mediums = new List<string>
            {
                "All",
                nameof(ItemType.Book),
                nameof(ItemType.Music),
                nameof(ItemType.Video)
            };

            selectedMedium = Mediums[0];
        }
    }
}
