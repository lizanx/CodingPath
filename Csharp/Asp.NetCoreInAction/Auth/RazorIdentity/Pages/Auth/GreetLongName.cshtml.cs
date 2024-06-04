using System.Security.Claims;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;

namespace RazorIdentity.Pages.Auth;

public class GreetLongNameModel : PageModel
{
    public string FullName { get; private set; } = default!;

    private readonly IAuthorizationService _authService;

    public GreetLongNameModel(IAuthorizationService authorizationService)
    {
        _authService = authorizationService;
    }

    public async Task<IActionResult> OnGetAsync()
    {
        var result = await _authService.AuthorizeAsync(User, "NameLength>4");

        if (result.Succeeded)
        {
            FullName = User.FindFirstValue("FullName")!;
            return Page();
        }

        return Forbid();
    }
}
