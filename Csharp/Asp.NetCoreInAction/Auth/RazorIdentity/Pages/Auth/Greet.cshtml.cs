using System.Security.Claims;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;

namespace RazorIdentity.Pages.Auth;

[Authorize("HasName")]
public class GreetPageModel : PageModel
{
    public string FullName { get; private set; } = default!;

    public IActionResult OnGet()
    {
        FullName = User.FindFirstValue("FullName")!;
        return Page();
    }
}
