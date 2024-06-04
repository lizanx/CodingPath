using Microsoft.AspNetCore.Authorization;

namespace RazorIdentity.Auth.Requirement;

class NameLengthRequirement : IAuthorizationRequirement
{
    public int MinLength { get; }

    public NameLengthRequirement(int minLength)
    {
        MinLength = minLength;
    }
}
