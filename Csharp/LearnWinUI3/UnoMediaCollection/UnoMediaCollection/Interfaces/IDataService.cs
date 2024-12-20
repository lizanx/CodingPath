using UnoMediaCollection.Enums;
using UnoMediaCollection.Models;
using System.Collections.Generic;

namespace UnoMediaCollection.Interfaces
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
    }
}
