using System;
using System.Linq;
using System.Text;
using Avalonia.Data;
using Avalonia.Data.Converters;
using Avalonia.Markup.Xaml;

namespace GetStartedApp.MarkupExtensions;

public class AddBinding : MarkupExtension
{
    private readonly BindingBase _leftOperand;
    private readonly BindingBase _rightOperand;

    public AddBinding(BindingBase leftOperand, BindingBase rightOperand)
    {
        _leftOperand = leftOperand;
        _rightOperand = rightOperand;
    }
    
    public override object ProvideValue(IServiceProvider serviceProvider)
    {
        var bindings = new MultiBinding()
        {
            Bindings = [_leftOperand, _rightOperand],
            Converter = new FuncMultiValueConverter<double, string>(operands =>
            {
                var sb = new StringBuilder();
                sb.Append("Sum of ");
                double sum = 0;
                foreach (double operand in operands)
                {
                    sb.Append($"{operand:0.00} ");
                    sum += operand;
                }

                sb.Append($"is {sum}");
                return sb.ToString();
            })
        };

        return bindings;
    }
}