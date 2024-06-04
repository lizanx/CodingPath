using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;

namespace RazorIdentity.Pages.Auth;

public class GmailCheckModel : PageModel
{
    private IAuthorizationService _authService;

    public GmailCheckModel(IAuthorizationService authService)
    {
        _authService = authService;
    }

    public async Task<IActionResult> OnGetAsync()
    {
        var authResult = await _authService.AuthorizeAsync(User, "Gmail");

        if (authResult.Succeeded)
        {
            return Page();
        }

        return Forbid();
    }
}
