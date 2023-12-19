namespace Northwind.Maui.Client;

public partial class CustomerDetailPage : ContentPage
{
	private CustomerListViewModel customers;
	public CustomerDetailPage(CustomerListViewModel customers)
	{
		InitializeComponent();

		this.customers = customers;
		BindingContext = new CustomerDetailViewModel();
		Title = "Add Customer";
	}

    public CustomerDetailPage(CustomerListViewModel customers,
		CustomerDetailViewModel customer)
    {
        InitializeComponent();

        this.customers = customers;
		BindingContext = customer;
		InsertButton.IsVisible = false;
    }

    private async void InsertButton_Clicked(object sender, EventArgs e)
    {
		customers.Add(BindingContext as  CustomerDetailViewModel);
		await Navigation.PopAsync(animated: true);
    }
}