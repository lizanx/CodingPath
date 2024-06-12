using ConfigWithDI.Services;
using Microsoft.Extensions.Options;

namespace ConfigWithDI;

class ConfigureGuidOptions : IConfigureOptions<GuidConfig>
{
    private readonly IServiceProvider _serviceProvider;

    // The injected provider is root service provider with singleton lifetime.
    // Cannot inject scoped service here, since this config-options is singleton.
    public ConfigureGuidOptions(IServiceProvider serviceProvider)
    {
        _serviceProvider = serviceProvider;
    }

    public void Configure(GuidConfig config)
    {
        // Create a scope from root provider to resolve scoped services.
        using var scope = _serviceProvider.CreateScope();
        var guidService = scope.ServiceProvider.GetRequiredService<IGuidService>();
        config.Guids = guidService.GetGuids(config.Count);
    }
}
