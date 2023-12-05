1. Use `@model T` to declare model type at top of the file, and use `@Model` to refer to the model in below codes.  
Strongly typed Razor views can enable linting and prevent errors.
2. Add `@addTagHelper *, Microsoft.AspNetCore.Mvc.TagHelpers` in _ViewImports.cshtml
3. Tag Helpers are more consistent with HTML format, while HTML Helpers may have more functionalities.  
And Tag Helpers cannot be used in Razor Components, in which case HTML Helpers are necessary.
4. Append "culture=*" as query string, or use `Accept-Language` in header.
5. Add resource files and use `IViewLocalizer`(Add service, use the middleware, inject in view templates).
6. `asp-`
7. Use Tag Helper `asp-all-route-data`.
8. Use attributes like `expires-after` / `expires-on`.
9. To display different contents for different users: developer/visitor/test.
10. With a `t` attribute and hash value of the file.
