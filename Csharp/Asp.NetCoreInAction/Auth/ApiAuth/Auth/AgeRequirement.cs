using Microsoft.AspNetCore.Authorization;

namespace ApiAuth.Auth;

class AgeRequirement : IAuthorizationRequirement
{
    public int MinAge { get; }
    
    public int MaxAge { get; }

    public AgeRequirement(int minAge, int maxAge)
    {
        MinAge = minAge;
        MaxAge = maxAge;
    }
}
