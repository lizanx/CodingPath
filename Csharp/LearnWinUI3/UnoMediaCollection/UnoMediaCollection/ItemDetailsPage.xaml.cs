using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Controls.Primitives;
using Microsoft.UI.Xaml.Data;
using Microsoft.UI.Xaml.Input;
using Microsoft.UI.Xaml.Media;
using Microsoft.UI.Xaml.Navigation;
using UnoMediaCollection.ViewModels;
using Windows.Foundation;
using Windows.Foundation.Collections;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=234238

namespace UnoMediaCollection;
/// <summary>
/// An empty page that can be used on its own or navigated to within a Frame.
/// </summary>
public sealed partial class ItemDetailsPage : Page
{
    public ItemDetailsViewModel ViewModel;

    public ItemDetailsPage()
    {
        ViewModel = App.HostContainer!.Services.GetRequiredService<ItemDetailsViewModel>();

        this.InitializeComponent();
    }

    protected override void OnNavigatedTo(NavigationEventArgs e)
    {
        base.OnNavigatedTo(e);

        var itemId = (int)e.Parameter;

        if (itemId > 0)
        {
            ViewModel.InitializeItemDetailData(itemId);
        }
    }
}
