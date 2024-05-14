namespace WeatherClient
{
    public partial class MainPage : ContentPage
    {
        public MainPage()
        {
            InitializeComponent();
        }

        private async void btnRefresh_Clicked(object sender, EventArgs e)
        {
            btnRefresh.IsEnabled = false;
            actIsBusy.IsRunning = true;

            BindingContext = await Services.WeatherServer.GetWeather(txtPostalCode.Text);

            //Models.WeatherData weatherData = await Services.WeatherServer.GetWeather(txtPostalCode.Text);

            //lblWind.Text = weatherData.Wind.ToString();
            //lblHumidity.Text = weatherData.Humidity.ToString();
            //lblPrecipitation.Text = weatherData.Precipitation.ToString();
            //lblTemperature.Text = weatherData.Temperature.ToString("#");

            //imgCondition.Source = weatherData.Condition switch
            //{
            //    Models.WeatherType.Sunny => ImageSource.FromFile("sunny.png"),
            //    Models.WeatherType.Cloudy => ImageSource.FromFile("cloud.png"),
            //    _ => ImageSource.FromFile("question.png")
            //};

            btnRefresh.IsEnabled = true;
            actIsBusy.IsRunning = false;
        }
    }

}
