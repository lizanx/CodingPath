using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using Avalonia.Data.Converters;

namespace GetStartedApp.Converters;

public class FullNameMultiConverter : IMultiValueConverter
{
    public object? Convert(IList<object?> values, Type targetType, object? parameter, CultureInfo culture)
    {
        if (values.Count == 0
            || !values.All(x => x is string or null)
            || !values.Any(x => x is string s && !string.IsNullOrWhiteSpace(s)))
        {
            throw new NotSupportedException();
        }

        var sb = new StringBuilder();
        foreach (var str in values)
        {
            if (str is string s && !string.IsNullOrWhiteSpace(s))
            {
                sb.Append(sb.Length > 0 ? " " + str : str);
            }
        }
        
        return sb.ToString();
    }
}