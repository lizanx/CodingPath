using Quartz;

namespace TryQuartz;

public class MyJob : IJob
{
    private readonly ScopedService _jobService;

    private readonly ILogger _logger;

    public MyJob(ScopedService scopedService, ILogger<MyJob> logger)
    {
        _jobService = scopedService;
        _logger = logger;
    }

    public Task Execute(IJobExecutionContext context)
    {
        var count = Random.Shared.Next(1, 6);

        Console.WriteLine("{0} languages selected:", count);
        foreach (string language in _jobService.GetLanguages(count))
        {
            Console.WriteLine("\tGot language: {0}", language);
        }

        return Task.CompletedTask;
    }
}
