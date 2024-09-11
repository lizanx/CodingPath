using System;
using Avalonia.Markup.Xaml;

namespace GetStartedApp.MarkupExtensions;

public class AddLiteral : MarkupExtension
{
    private double _leftOperand;
    private double _rightOperand;

    public AddLiteral(double leftOperand, double rightOperand)
    {
        _leftOperand = leftOperand;
        _rightOperand = rightOperand;
    }
    
    public override object ProvideValue(IServiceProvider serviceProvider)
    {
        return $"{_leftOperand + _rightOperand}";
    }
}
