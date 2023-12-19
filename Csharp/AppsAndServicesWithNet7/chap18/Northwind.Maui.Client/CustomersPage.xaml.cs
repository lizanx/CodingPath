namespace Northwind.Maui.Client;

public partial class CustomersPage : ContentPage
{
	public CustomersPage()
	{
		InitializeComponent();

		CustomerListViewModel viewModel = new ();
		viewModel.AddSampleData();
		BindingContext = viewModel;
	}

    private async void Customer_Tapped(object sender, ItemTappedEventArgs e)
    {
		if (e.Item is not CustomerDetailViewModel c) return;

		await Navigation.PushAsync(new CustomerDetailPage(
			BindingContext as CustomerListViewModel, c));
    }

    private async void Customers_Refreshing(object sender, EventArgs e)
    {
		if (sender is not ListView listView) return;

		listView.IsRefreshing = true;

		// simulate a refresh
		await Task.Delay(1500);

		listView.IsRefreshing = false;
    }

    private void Customer_Deleted(object sender, EventArgs e)
    {
		MenuItem menuItem = sender as MenuItem;
		if (menuItem.BindingContext is not CustomerDetailViewModel c) return;
		(BindingContext as CustomerListViewModel).Remove(c);
    }

    private async void Customer_Phoned(object sender, EventArgs e)
    {
        MenuItem menuItem = sender as MenuItem;
        if (menuItem.BindingContext is not CustomerDetailViewModel c) return;

		if (await DisplayAlert("Dial a number", "Would you like to call" +
			c.Phone + " ?", "Yes", "No"))
		{
			try
			{
				if (PhoneDialer.IsSupported)
				{
					PhoneDialer.Open(c.Phone);
				}			
			}
			catch (Exception ex)
			{
				await DisplayAlert(title: "Failed", message: string.Format(
					"Failed to dial {0} due to {1}", c.Phone, ex.Message),
					cancel: "OK");
			}
		}
    }

    private async void Add_Clicked(object sender, EventArgs e)
    {
		await Navigation.PushAsync(new CustomerDetailPage(
			BindingContext as CustomerListViewModel));
    }
}