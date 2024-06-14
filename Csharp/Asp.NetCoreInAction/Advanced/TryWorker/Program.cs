using TryWorker;

var builder = Host.CreateApplicationBuilder(args);
builder.Services.AddHostedService<Worker>();
// Register the worker in Windows services.
builder.Services.AddWindowsService(options =>
{
    options.ServiceName = "Lizan's Test Service";
});

var host = builder.Build();
host.Run();
