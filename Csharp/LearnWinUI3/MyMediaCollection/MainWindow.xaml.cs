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
        public MainWindow()
        {
            this.InitializeComponent();
            PopulateData();
        }

        private void PopulateData()
        {
            if (_isLoaded) return;
            _isLoaded = true;

            _items = new List<MediaItem>()
            {
                new () {
                    Id = 1,
                    Name = "Classical Favorites",
                    MediaType = ItemType.Music,
                    MediaInfo = new () {
                        Id = 1,
                        MediaType = ItemType.Music,
                        Name = "CD"
                    }
                },
                new () {
                    Id = 2,
                    Name = "Classic Fairy Tales",
                    MediaType = ItemType.Book,
                    MediaInfo = new () {
                        Id = 2,
                        MediaType = ItemType.Book,
                        Name = "Book"
                    }
                },
                new () {
                    Id = 3,
                    Name = "The Mummy",
                    MediaType = ItemType.Video,
                    MediaInfo = new () {
                        Id = 3,
                        MediaType = ItemType.Video,
                        Name = "Blu Ray"
                    }
                }
            };
        }

        private bool _isLoaded;
        private IList<MediaItem> _items { get; set; }
    }
}
