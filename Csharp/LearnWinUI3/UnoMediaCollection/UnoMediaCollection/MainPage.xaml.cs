namespace UnoMediaCollection;

using Microsoft.UI.Xaml.Navigation;
using UnoMediaCollection.ViewModels;

public sealed partial class MainPage : Page
{
    public MainViewModel ViewModel;

    public MainPage()
    {
        ViewModel = App.HostContainer!.Services.GetRequiredService<MainViewModel>();

        this.InitializeComponent();
    }

    protected override void OnNavigatedTo(NavigationEventArgs e)
    {
        base.OnNavigatedTo(e);

        if (e.NavigationMode == NavigationMode.Back)
        {
            ViewModel.PopulateData();
        }
    }
}
