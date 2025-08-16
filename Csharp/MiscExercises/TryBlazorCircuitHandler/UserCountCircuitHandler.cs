using Microsoft.AspNetCore.Components.Server.Circuits;

namespace TryBlazorCircuitHandler;

public class UserCountCircuitHandler : CircuitHandler
{
    public UserCountCircuitHandler(ConcurrentUsersService userService)
    {
        _userService = userService;
    }
    
    public override Task OnCircuitOpenedAsync(Circuit circuit, CancellationToken cancellationToken)
    {
        _userService.UserCount += 1;
        return base.OnCircuitOpenedAsync(circuit, cancellationToken);
    }

    public override Task OnCircuitClosedAsync(Circuit circuit, CancellationToken cancellationToken)
    {
        _userService.UserCount -= 1;
        return base.OnCircuitClosedAsync(circuit, cancellationToken);
    }

    private readonly ConcurrentUsersService _userService;
}