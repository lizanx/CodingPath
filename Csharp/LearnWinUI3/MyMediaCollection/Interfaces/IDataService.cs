using MyMediaCollection.Enums;
using MyMediaCollection.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MyMediaCollection.Interfaces
{
    public interface IDataService
    {
        IList<MediaItem> GetItems();
        MediaItem GetItem(int id);
        int AddItem(MediaItem item);
        void UpdateItem(MediaItem item);

        IList<ItemType> GetItemTypes();

        Medium GetMedium(string name);
        IList<Medium> GetMediums();
        IList<Medium> GetMediums(ItemType itemType);

        IList<LocationType> GetLocationTypes();

        int SelectedItemId { get; set; }
    }
}
