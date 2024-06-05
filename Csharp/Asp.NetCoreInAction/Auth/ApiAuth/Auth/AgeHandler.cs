using System.Security.Claims;
using Microsoft.AspNetCore.Authorization;

namespace ApiAuth.Auth;

class AgeHandler : AuthorizationHandler<AgeRequirement>
{
    protected override Task HandleRequirementAsync(AuthorizationHandlerContext context, AgeRequirement requirement)
    {
        if (context.User.FindFirstValue("Age") is string ageStr)
        {
            int age = int.Parse(ageStr);
            if (age >= requirement.MinAge && age <= requirement.MaxAge)
            {
                context.Succeed(requirement);
            }
        }

        return Task.CompletedTask;
    }
}
