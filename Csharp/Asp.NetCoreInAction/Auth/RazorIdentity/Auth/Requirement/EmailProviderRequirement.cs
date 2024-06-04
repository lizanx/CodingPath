using Microsoft.AspNetCore.Authorization;

namespace RazorIdentity.Auth.Requirement;

class EmailProviderRequirement : IAuthorizationRequirement
{
    public string EmailProvider { get; }

    public EmailProviderRequirement(string emailProvider)
    {
        EmailProvider = emailProvider;
    }
}
