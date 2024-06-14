using TryQuartz;
using Quartz;

var builder = Host.CreateApplicationBuilder(args);
// builder.Services.AddHostedService<Worker>();

builder.Services.AddScoped<ScopedService>();
builder.Services.AddQuartzHostedService(options =>
    options.WaitForJobsToComplete = true);
builder.Services.AddQuartz(qConfig =>
{
    var jobKey = new JobKey("My Quartz Job");
    qConfig.AddJob<MyJob>(opts =>
        opts.WithIdentity(jobKey));
    
    qConfig.AddTrigger(opts =>
        opts.ForJob(jobKey)
        .WithIdentity(jobKey.Name + " Trigger")
        .StartNow()
        .WithSimpleSchedule(schedule =>
            schedule.WithIntervalInSeconds(10)
            .RepeatForever()));
});

var host = builder.Build();
host.Run();
