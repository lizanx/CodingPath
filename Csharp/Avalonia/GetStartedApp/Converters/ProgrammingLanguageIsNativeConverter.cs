using System;
using System.Globalization;
using Avalonia.Data;
using Avalonia.Data.Converters;

namespace GetStartedApp.Converters;

public class ProgrammingLanguageIsNativeConverter : IValueConverter
{
    public static readonly ProgrammingLanguageIsNativeConverter Instance = new();

    public object? Convert(object? value, Type targetType, object? parameter, CultureInfo culture)
    {
        if (value is ProgrammingLanguageItemViewModel.ExecutionType languageExecutionType
            && targetType.IsAssignableFrom(typeof(bool)))
        {
            var result = languageExecutionType == ProgrammingLanguageItemViewModel.ExecutionType.NativeCompiled ? true : false;
            if (parameter is string s)
            {
                if (s == "not")
                {
                    return !result;
                }
            }

            return result;
        }

        return new BindingNotification(new InvalidCastException(), BindingErrorType.Error);
    }

    public object? ConvertBack(object? value, Type targetType, object? parameter, CultureInfo culture)
    {
        throw new NotImplementedException();
    }
}