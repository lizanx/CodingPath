using Microsoft.Data.SqlClient;
using System.Data;

SqlConnectionStringBuilder builder = new()
{
    InitialCatalog = "Northwind",
    MultipleActiveResultSets = true,
    Encrypt = true,
    TrustServerCertificate = true,
    ConnectTimeout = 10
};

WriteLine("Connect to:");
WriteLine(" 1 - SQL Server on local machine");
WriteLine(" 2 - Azure SQL Database");
WriteLine(" 3 - Azure SQL Edge");
WriteLine();
Write("Press a key: ");
ConsoleKey key = ReadKey().Key;
WriteLine();
WriteLine();
switch (key)
{
    case ConsoleKey.NumPad1:
    case ConsoleKey.D1:
        builder.DataSource = "."; // Local SQL Server
        break;
    case ConsoleKey.NumPad2:
    case ConsoleKey.D2:
        builder.DataSource = "tcp:apps-services-net7.database.windows.net,1433"; // Azure SQL Database
        break;
    case ConsoleKey.NumPad3:
    case ConsoleKey.D3:
        builder.DataSource = "tcp:127.0.0.1,1433"; // Azure SQL Edge
        break;
    default:
        WriteLine("No data source selected.");
        return;
}

WriteLine("Authentication using:");
WriteLine(" 1 - Windows Integrated Security");
WriteLine(" 2 - SQL Login, for example, sa");
WriteLine();
Write("Press a key: ");
key = ReadKey().Key;
WriteLine();
WriteLine();
switch (key)
{
    case ConsoleKey.NumPad1:
    case ConsoleKey.D1:
        builder.IntegratedSecurity = true;
        break;
    case ConsoleKey.NumPad2:
    case ConsoleKey.D2:
        builder.UserID = "sa"; // Azure SQL Edge

        Write("Enter your SQL Server password: ");
        string? pwd = ReadLine();
        if (string.IsNullOrEmpty(pwd))
        {
            WriteLine("Password cannot be empty or null.");
            return;
        }

        builder.Password = pwd;
        builder.PersistSecurityInfo = false;
        break;
    default:
        WriteLine("No authentication selected.");
        return;
}

SqlConnection connection = new(builder.ConnectionString);
WriteLine($"Connection String: {connection.ConnectionString}");
WriteLine();

connection.StateChange += Connection_StateChange;
connection.InfoMessage += Connection_InfoMessage;

try
{
    WriteLine($"Opening connection, please wait up to {builder.ConnectTimeout} seconds...");
    WriteLine();
    await connection.OpenAsync();

    WriteLine($"SQL Server version: {connection.ServerVersion}");

    connection.StatisticsEnabled = true;
}
catch (SqlException ex)
{
    WriteLine($"SQL Exception: {ex}");
    return;
}


Write("Enter a unit price: ");
string? priceText = ReadLine();
if (!decimal.TryParse(priceText, out decimal price))
{
    WriteLine("You must enter a valid unit price.");
    connection.Close();
    return;
}
SqlCommand cmd = connection.CreateCommand();
cmd.CommandType = CommandType.Text;
cmd.CommandText = "SELECT ProductId, ProductName, UnitPrice FROM Products " +
    "WHERE UnitPrice > @price";
cmd.Parameters.AddWithValue("price", price);
SqlDataReader r = await cmd.ExecuteReaderAsync();
WriteLine("----------------------------------------------------------");
WriteLine("| {0,5} | {1,-35} | {2,8} |", "Id", "Name", "Price");
WriteLine("----------------------------------------------------------");
while (r.Read())
{
    WriteLine("| {0,5} | {1,-35} | {2,8:C} |",
        await r.GetFieldValueAsync<int>("ProductId"),
        await r.GetFieldValueAsync<string>("ProductName"),
        await r.GetFieldValueAsync<decimal>("UnitPrice"));
}
WriteLine("----------------------------------------------------------");
await r.CloseAsync();

await connection.CloseAsync();
