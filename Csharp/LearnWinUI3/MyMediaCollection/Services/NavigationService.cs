using Microsoft.UI.Xaml.Controls;
using MyMediaCollection.Interfaces;
using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MyMediaCollection.Services
{
    class NavigationService : INavigationService
    {
        public const string RootPage = "(Root)";
        public const string UnknownPage = "(Unknown)";
        private readonly IDictionary<string, Type> _pages = new ConcurrentDictionary<string, Type>();
        private static Frame AppFrame;

        public NavigationService(Frame rootFrame)
        {
            AppFrame = rootFrame;
        }

        public void Configure(string page, Type type)
        {
            if (_pages.Values.Any(x => x == type))
            {
                throw new ArgumentException($"The {type.Name} view has already been registered under another name.");
            }
            _pages[page] = type;
        }

        public string CurrentPage
        {
            get
            {
                var frame = AppFrame;

                if (frame.BackStackDepth == 0)
                    return RootPage;

                if (frame.Content == null)
                    return UnknownPage;

                var type = frame.Content.GetType();
                if (_pages.Values.All(x => x != type))
                    return UnknownPage;

                var item = _pages.Single(i => i.Value == type);
                return item.Key;
            }
        }

        public void NavigateTo(string page) =>
            NavigateTo(page, null);
        
        public void NavigateTo(string page, object parameter)
        {
            if (!_pages.ContainsKey(page))
                throw new ArgumentException($"Unable to find a page registered with name {page}.");

            AppFrame.Navigate(_pages[page], parameter);
        }

        public void GoBack()
        {
            if (AppFrame?.CanGoBack == true)
            {
                AppFrame.GoBack();
            }
        }
    }
}
