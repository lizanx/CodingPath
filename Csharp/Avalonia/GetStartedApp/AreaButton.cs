using Avalonia.Controls;
using Avalonia.Controls.Metadata;
using Avalonia.Input;

namespace GetStartedApp;

[PseudoClasses(":left", ":right", ":middle")]
public class AreaButton : Button
{    
    protected override void OnPointerMoved(PointerEventArgs e)
    {
        base.OnPointerMoved(e);
        var pos = e.GetPosition(this);

        if (pos.X < Bounds.Width * 0.25)
            SetAreaPseudoClasses(true, false, false);
        else if (pos.X > Bounds.Width * 0.75)
            SetAreaPseudoClasses(false, true, false);
        else
            SetAreaPseudoClasses(false, false, true);
    }

    protected override void OnPointerExited(PointerEventArgs e)
    {
        base.OnPointerExited(e);
        SetAreaPseudoClasses(false, false, false);
    }

    private void SetAreaPseudoClasses(bool left, bool right, bool middle)
    {
        PseudoClasses.Set(":left", left);
        PseudoClasses.Set(":right", right);
        PseudoClasses.Set(":middle", middle);
    }
}