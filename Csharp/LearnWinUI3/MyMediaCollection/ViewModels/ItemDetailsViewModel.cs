using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using MyMediaCollection.Enums;
using MyMediaCollection.Interfaces;
using MyMediaCollection.Model;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MyMediaCollection.ViewModels
{
    public partial class ItemDetailsViewModel : ObservableObject
    {
        [ObservableProperty]
        private ObservableCollection<string> locationTypes = [];
        [ObservableProperty]
        private ObservableCollection<string> mediums = [];
        [ObservableProperty]
        private ObservableCollection<string> itemTypes = [];
        [ObservableProperty]
        private string itemName;
        [ObservableProperty]
        private string selectedMedium;
        [ObservableProperty]
        private string selectedItemType;
        [ObservableProperty]
        private string selectedLocation;
        [ObservableProperty]
        //[NotifyCanExecuteChangedFor(nameof(SaveCommand))]
        private bool isDirty;

        private int _itemId;
        private int _selectedItemId = -1;
        protected INavigationService _navigationService;
        protected IDataService _dataService;

        public ItemDetailsViewModel(INavigationService navigationService, IDataService dataService)
        {
            _navigationService = navigationService;
            _dataService = dataService;
            PopulateLists();
        }

        private void PopulateLists()
        {
            ItemTypes.Clear();
            foreach (string itemType in Enum.GetNames(typeof(ItemType)))
            {
                ItemTypes.Add(itemType);
            }

            LocationTypes.Clear();
            foreach (string locationType in Enum.GetNames(typeof(LocationType)))
            {
                LocationTypes.Add(locationType);
            }

            Mediums = new ObservableCollection<string>();
        }

        public async Task InitializeItemDetailData(int itemId)
        {
            _selectedItemId = itemId;
            IsDirty = false;
            await PopulateExistingItem();
        }

        private async Task PopulateExistingItem()
        {
            if (_selectedItemId > 0)
            {
                var item = await _dataService.GetItemAsync(_selectedItemId);
                Mediums.Clear();
                foreach (string medium in _dataService.GetMediums(item.MediaType).Select(x => x.Name))
                {
                    Mediums.Add(medium);
                }

                _itemId = item.Id;
                ItemName = item.Name;
                SelectedItemType = item.MediaType.ToString();
                SelectedLocation = item.Location.ToString();
                SelectedMedium = item.MediumInfo.Name;
            }
        }

        //[RelayCommand(CanExecute = nameof(CanSaveItem))]
        private async Task SaveAsync()
        {
            if (_itemId > 0)
            {
                var item = await _dataService.GetItemAsync(_itemId);

                item.Name = ItemName;
                item.MediaType = (ItemType)Enum.Parse(typeof(ItemType), SelectedItemType);
                item.Location = (LocationType)Enum.Parse(typeof(LocationType), SelectedLocation);
                item.MediumInfo = _dataService.GetMedium(SelectedMedium);

                await _dataService.UpdateItemAsync(item);
            }
            else
            {
                MediaItem item = new()
                {
                    Name = ItemName,
                    MediaType = (ItemType)Enum.Parse(typeof(ItemType), SelectedItemType),
                    Location = (LocationType)Enum.Parse(typeof(LocationType), SelectedLocation),
                    MediumInfo = _dataService.GetMedium(SelectedMedium)
                };

                await _dataService.AddItemAsync(item);
            }
        }

        public async Task SaveItemAndContinueAsync()
        {
            await SaveAsync();
            _itemId = 0;
            ItemName = string.Empty;
            SelectedItemType = null;
            SelectedLocation = null;
            SelectedMedium = null;
            IsDirty = false;
        }

        public async Task SaveItemAndReturnAsync()
        {
            await SaveAsync();
            _navigationService.GoBack();
        }

        //private bool CanSaveItem() =>
        //    IsDirty;

        partial void OnItemNameChanged(string value)
        {
            IsDirty = true;
        }

        partial void OnSelectedMediumChanged(string value)
        {
            IsDirty = true;
        }

        partial void OnSelectedLocationChanged(string value)
        {
            IsDirty = true;
        }

       partial void OnSelectedItemTypeChanged(string value)
        {
            IsDirty = true;
            Mediums.Clear();

            if (!string.IsNullOrEmpty(value))
            {
                foreach (string med in _dataService.GetMediums((ItemType)Enum.Parse(typeof(ItemType), SelectedItemType)).Select(x => x.Name))
                {
                    Mediums.Add(med);
                }
            }
        }

        [RelayCommand]
        private void Cancel()
        {
            _navigationService.GoBack();
        }

    }
}
