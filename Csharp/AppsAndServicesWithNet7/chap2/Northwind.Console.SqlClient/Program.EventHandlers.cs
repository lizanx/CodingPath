using Microsoft.Data.SqlClient;
using System.Data;

partial class Program
{
    static void Connection_StateChange(object sender, StateChangeEventArgs e)
    {
        var prevColor = ForegroundColor;
        ForegroundColor = ConsoleColor.DarkYellow;
        WriteLine($"State changed from {e.OriginalState} to {e.CurrentState}.");
        ForegroundColor = prevColor;
    }

    static void Connection_InfoMessage(object sender, SqlInfoMessageEventArgs e)
    {
        var prevColor = ForegroundColor;
        ForegroundColor = ConsoleColor.DarkBlue;
        WriteLine($"Info: {e.Message}");
        foreach (SqlError err in e.Errors)
        {
            WriteLine($"\tError: {err.Message}");
        }
        ForegroundColor = prevColor;
    }
}