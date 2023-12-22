using CommunityToolkit.Maui.Alerts; // Toast
using CommunityToolkit.Maui.Core; // IToast, ToastDuration

namespace Northwind.Maui.Blazor.Client.Views;

public partial class OrdersPage : ContentPage
{
	private bool _isBatteryWatched;

	public OrdersPage()
	{
		InitializeComponent();
		UpdateBatteryInfo(Battery.Default);
	}

    private void NewWindowButton_Clicked(object sender, EventArgs e)
    {
		Window window = new() { Page = new AppShell() };
		Application.Current.OpenWindow(window);
    }

	private void BatterySwitch_Toggled(object sender, ToggledEventArgs e) =>
		WatchBattery(Battery.Default);

	private void WatchBattery(IBattery battery)
	{
		if (!_isBatteryWatched)
		{
			battery.BatteryInfoChanged += Battery_BatteryInfoChanged;
		}
		else
		{
			battery.BatteryInfoChanged -= Battery_BatteryInfoChanged;
		}

		_isBatteryWatched = !_isBatteryWatched;
	}

	private void Battery_BatteryInfoChanged(object sender, BatteryInfoChangedEventArgs e)
	{
		UpdateBatteryInfo(Battery.Default);
	}

	private void UpdateBatteryInfo(IBattery battery)
	{
		BatteryStateLabel.Text = battery.State switch
		{
			BatteryState.Charging => "Battery is currently charging",
			BatteryState.Discharging =>
				"Charger is not connected and the battery is discharging",
			BatteryState.Full => "Battery is full",
			BatteryState.NotCharging => "The battery is not charing.",
			BatteryState.NotPresent => "Battery is not available.",
			BatteryState.Unknown => "Battery is unknown.",
			_ => "Battery is unknown"
		};

		BatteryLevelLabel.Text =
			$"Battery is {battery.ChargeLevel * 100}% charged.";
	}

	private async void Menu_Clicked(object sender, EventArgs e)
	{
		MenuFlyoutItem menu = sender as MenuFlyoutItem;

		if (menu != null)
		{
			await Shell.Current.GoToAsync($"//{menu.CommandParameter}");
		}
	}

	private async void ToastMenu_Clicked(object sender, EventArgs e)
	{
		MenuFlyoutItem menu = sender as MenuFlyoutItem;

		if (menu != null )
		{
			IToast toast = Toast.Make(message: "This toast pops up.",
				duration: ToastDuration.Short, textSize: 18);

			await toast.Show();
		}
	}
}