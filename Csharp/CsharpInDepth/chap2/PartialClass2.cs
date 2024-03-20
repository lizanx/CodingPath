partial class PartialMethodsDemo
{
    partial void CustomizeToString(ref string text)
    {
        text += " - customized";
    }
}