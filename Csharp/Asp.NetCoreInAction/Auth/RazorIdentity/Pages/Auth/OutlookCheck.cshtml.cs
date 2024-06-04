using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;

namespace RazorIdentity.Pages.Auth;

public class OutlookCheckModel : PageModel
{
    private IAuthorizationService _authService;

    public OutlookCheckModel(IAuthorizationService authService)
    {
        _authService = authService;
    }

    public async Task<IActionResult> OnGetAsync()
    {
        var result = await _authService.AuthorizeAsync(User, "Outlook");

        if (result.Succeeded)
        {
            return Page();
        }

        return Forbid();
    }
}
