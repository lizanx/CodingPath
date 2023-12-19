using System.Net.Http.Headers;
using System.Net.Http.Json;

namespace Northwind.Maui.Client;

public partial class CustomersPage : ContentPage
{
	public CustomersPage()
	{
		InitializeComponent();

		CustomerListViewModel viewModel = new ();

		try
		{
			HttpClient client = new()
			{ BaseAddress = new Uri(DeviceInfo.Platform == DevicePlatform.Android ?
				"http://10.0.2.2:5182" : "http://localhost:5182")
			};

			InfoLabel.Text = $"BaseAddr: {client.BaseAddress}";

			client.DefaultRequestHeaders.Accept.Add(
				new MediaTypeWithQualityHeaderValue("application/json"));

			HttpResponseMessage response = client.GetAsync("api/customers").Result;

			response.EnsureSuccessStatusCode();

			IEnumerable<CustomerDetailViewModel> customersFromService =
				response.Content.ReadFromJsonAsync<IEnumerable<CustomerDetailViewModel>>().Result;
			
			foreach(CustomerDetailViewModel c in customersFromService.OrderBy(c => c.CompanyName))
			{
				viewModel.Add(c);
			}

			InfoLabel.Text += $"\n{viewModel.Count} customers loaded.";
		}
		catch (Exception ex)
		{
            ErrorLabel.Text = ex.Message + "\nUsing sample data instead.";
            ErrorLabel.IsVisible = true;
			viewModel.AddSampleData();
        }

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