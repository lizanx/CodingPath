namespace Phoneword
{
    public partial class MainPage : ContentPage
    {
        string translatedNumber;

        public MainPage()
        {
            InitializeComponent();
        }

        private void OnTranslate(object sender, EventArgs e)
        {
            string enteredNumber = PhoneNumberText.Text;
            translatedNumber = Core.PhonewordTranslator.ToNumber(enteredNumber);

            if (!string.IsNullOrEmpty(translatedNumber))
            {
                CallButton.Text = "Call " + translatedNumber;
                CallButton.IsEnabled = true;
            }
            else
            {
                CallButton.Text = "Call";
                CallButton.IsEnabled = false;
            }
        }

        private async void OnCall(object sender, EventArgs e)
        {
            if (await DisplayAlert("Dial a number", "Would you like to call " + translatedNumber + "?", "Yes", "No"))
            {
                try
                {
                    if (PhoneDialer.Default.IsSupported)
                    {
                        PhoneDialer.Default.Open(translatedNumber);
                    }
                }
                catch (ArgumentNullException)
                {
                    await DisplayAlert("Unable to dial", "Phone number was not valid.", "OK");
                }
                catch (Exception)
                {
                    await DisplayAlert("Unable to dial", "Phone dialing failed.", "OK");
                }
            }
        }
    }

}
