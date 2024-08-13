using System.Text;

namespace TryNuget;

public static class StringExtensions
{
    public static string Repeat(this string str, int n)
    {
        if (n <= 0)
            return string.Empty;

        var sb = new StringBuilder();
        for (int i = 0; i < n; i++)
        {
            sb.Append(str);
        }
        return sb.ToString();
    }
}
