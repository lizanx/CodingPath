namespace Packt.Shared;

public static class NorthwindExtensionMethods
{
    public static string ConvertToBase64Jpeg(this byte[] picture)
    {
        return string.Format("data:image/jpg;base64,{0}",
            Convert.ToBase64String(picture));
    }
}