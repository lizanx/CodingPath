using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using RazorIdentity.Auth.Requirement;

namespace RazorIdentity.Auth.Handler;

class EmailProviderHandler : AuthorizationHandler<EmailProviderRequirement>
{
    private readonly UserManager<IdentityUser> _userManager;
    
    public EmailProviderHandler(UserManager<IdentityUser> userManager)
    {
        _userManager = userManager;
    }

    protected override async Task HandleRequirementAsync(
        AuthorizationHandlerContext context,
        EmailProviderRequirement requirement
    )
    {
        if ((await _userManager.GetUserAsync(context.User)) is IdentityUser user)
        {
            if (user.Email?.Contains(requirement.EmailProvider) ?? false)
            {
                context.Succeed(requirement);
            }
        }
    }
}
