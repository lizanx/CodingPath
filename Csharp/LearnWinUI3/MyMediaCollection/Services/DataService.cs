using MyMediaCollection.Enums;
using MyMediaCollection.Interfaces;
using MyMediaCollection.Model;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MyMediaCollection.Services
{
    class DataService : IDataService
    {
        private IList<MediaItem> _items;
        private IList<ItemType> _itemTypes;
        private IList<Medium> _mediums;
        private IList<LocationType> _locationTypes;
        
        public int SelectedItemId { get; set; }

        public DataService()
        {
            PopulateItemTypes();
            PopulateMediums();
            PopulateLocationTypes();
            PopulateItems();
        }

        public IList<MediaItem> GetItems() =>
            _items;

        public MediaItem GetItem(int id) =>
            _items.FirstOrDefault(x => x.Id == id);

        public int AddItem(MediaItem item)
        {
            item.Id = _items.Max(x => x.Id) + 1;
            _items.Add(item);

            return item.Id;
        }

        public void UpdateItem(MediaItem item)
        {
            var matchedItem = _items.FirstOrDefault(x => x.Id == item.Id);
            if (matchedItem != null)
            {
                _items[item.Id - 1] = item;
            }
        }

        public IList<ItemType> GetItemTypes() =>
            _itemTypes;

        public Medium GetMedium(string name) =>
            _mediums.FirstOrDefault(x => x.Name == name);

        public IList<Medium> GetMediums() =>
            _mediums;

        public IList<Medium> GetMediums(ItemType itemType) =>
            _mediums.Where(x => x.MediaType == itemType).ToList();

        public IList<LocationType> GetLocationTypes() =>
            _locationTypes;



        private void PopulateItems()
        {
            var cd = new MediaItem
            {
                Id = 1,
                Name = "Classical Favorites",
                MediaType = ItemType.Music,
                MediumInfo = _mediums.FirstOrDefault(m => m.Name == "CD"),
                Location = LocationType.InCollection
            };

            var book = new MediaItem
            {
                Id = 2,
                Name = "Classic Fairy Tales",
                MediaType = ItemType.Book,
                MediumInfo = _mediums.FirstOrDefault(m => m.Name == "Hardcover"),
                Location = LocationType.InCollection
            };

            var bluRay = new MediaItem
            {
                Id = 3,
                Name = "The Mummy",
                MediaType = ItemType.Video,
                MediumInfo = _mediums.FirstOrDefault(m => m.Name == "Blu Ray"),
                Location = LocationType.InCollection
            };

            _items = new List<MediaItem>
            {
                cd,
                book,
                bluRay
            };
        }

        private void PopulateMediums()
        {
            var cd = new Medium { Id = 1, MediaType = ItemType.Music, Name = "CD" };
            var vinyl = new Medium { Id = 2, MediaType = ItemType.Music, Name = "Vinyl" };
            var hardcover = new Medium { Id = 3, MediaType = ItemType.Book, Name = "Hardcover" };
            var paperback = new Medium { Id = 4, MediaType = ItemType.Book, Name = "Paperback" };
            var dvd = new Medium { Id = 5, MediaType = ItemType.Video, Name = "DVD" };
            var bluRay = new Medium { Id = 6, MediaType = ItemType.Video, Name = "Blu Ray" };

            _mediums = new List<Medium>
            {
                cd,
                vinyl,
                hardcover,
                paperback,
                dvd,
                bluRay
            };
        }

        private void PopulateItemTypes()
        {
            _itemTypes = new List<ItemType>
            {
                ItemType.Book,
                ItemType.Music,
                ItemType.Video
            };
        }

        private void PopulateLocationTypes()
        {
            _locationTypes = new List<LocationType>
            {
                LocationType.InCollection,
                LocationType.Loaned
            };
        }
    }
}
