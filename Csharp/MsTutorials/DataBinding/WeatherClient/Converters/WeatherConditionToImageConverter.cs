using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WeatherClient.Models;

namespace WeatherClient.Converters
{
    internal class WeatherConditionToImageConverter : IValueConverter
    {
        public object? Convert(object? value, Type tartgetType, object? parameter, CultureInfo culture)
        {
            WeatherType weatherCondition = (WeatherType)value!;

            return weatherCondition switch
            {
                Models.WeatherType.Cloudy => ImageSource.FromFile("cloud.png"),
                Models.WeatherType.Sunny => ImageSource.FromFile("sunny.png"),
                _ => ImageSource.FromFile("question.png")
            };
        }

        public object? ConvertBack(object? value, Type tartgetType, object? parameter, CultureInfo culture) =>
            throw new NotImplementedException();
    }
}
