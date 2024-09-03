using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using Avalonia;
using Avalonia.Data;
using Avalonia.Data.Converters;
using Avalonia.Media;
using Avalonia.Media.Immutable;

namespace GetStartedApp.Converters;

public sealed class RgbToBrushMultiConverter : IMultiValueConverter
{
    public object? Convert(IList<object?> values, Type targetType, object? parameter, CultureInfo culture)
    {
        if (values?.Count != 3 || !targetType.IsAssignableFrom(typeof(ImmutableSolidColorBrush)))
        {
            throw new NotSupportedException();
        }

        if (!values.All(v => v is decimal or UnsetValueType or null))
        {
            throw new NotSupportedException();
        }

        if (values[0] is not decimal r
            || values[1] is not decimal g
            || values[2] is not decimal b)
        {
            return BindingOperations.DoNothing;
        }

        const byte alpha = 255;
        var color = new Color(alpha, (byte)r, (byte)g, (byte)b);
        return new ImmutableSolidColorBrush(color);
    }
}