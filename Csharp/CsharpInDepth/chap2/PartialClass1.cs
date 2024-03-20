partial class PartialMethodsDemo
{
    public PartialMethodsDemo()
    {
        OnConstruction();
    }

    public override string ToString()
    {
        string ret = "Original return value";
        CustomizeToString(ref ret);
        return ret;
    }

    partial void OnConstruction();
    partial void CustomizeToString(ref string text);
}