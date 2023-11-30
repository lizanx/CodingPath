using Microsoft.AspNetCore.SignalR.Client;
using Northwind.SignalR.Streams;

Write("Enter a stock(press ENTER for MSFT): ");
string? stock = ReadLine();
if (string.IsNullOrEmpty(stock))
{
    stock = "MSFT";
}

HubConnection hubConnection = new HubConnectionBuilder()
    .WithUrl("https://localhost:5131/stockprice")
    .Build();

await hubConnection.StartAsync();

try
{
    CancellationTokenSource cts = new();

    IAsyncEnumerable<StockPrice> stockPrices =
        hubConnection.StreamAsync<StockPrice>(methodName: "GetStockPriceUpdates",
            stock, cts.Token);
    
    await foreach (StockPrice sp in stockPrices)
    {
        WriteLine($"{sp.Stock} is now {sp.Price:C}");

        Write("Do you want to cancel (y/n)? ");
        ConsoleKey key = ReadKey().Key;
        if (key == ConsoleKey.Y)
        {
            cts.Cancel();
        }

        WriteLine();
    }
}
catch (Exception ex)
{
    WriteLine($"{ex.GetType()} says {ex.Message}");
}
WriteLine();

WriteLine("Streaming download completed.");

await hubConnection.SendAsync(methodName: "UploadStocks", GetStockAsync());

WriteLine("Uploading stocks...(press ENTER to stop)");
ReadLine();

WriteLine("Ending console app.");
