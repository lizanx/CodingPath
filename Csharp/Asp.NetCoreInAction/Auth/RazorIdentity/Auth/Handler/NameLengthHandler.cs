using System.Security.Claims;
using Microsoft.AspNetCore.Authorization;
using RazorIdentity.Auth.Requirement;

namespace RazorIdentity.Auth.Handler;

class NameLengthHandler : AuthorizationHandler<NameLengthRequirement>
{
    protected override Task HandleRequirementAsync(
        AuthorizationHandlerContext context,
        NameLengthRequirement requirement
    )
    {
        if (context.User.FindFirst("FullName") is Claim claim)
        {
            if (claim.Value.Length >= requirement.MinLength)
            {
                context.Succeed(requirement);
            }
        }

        return Task.CompletedTask;
    }
}
