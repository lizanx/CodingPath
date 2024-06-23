1. What is the difference between authentication and authorization?
> Authentication is to  determine who the user is, authorization is to determine if 
> the authenticated user has the right to access certain resources.

2. If you add a Secure component to the Home page, will the user need to be authenticated to render it?
> No, `[Authorize]` attribute can only be applied to routable pages.

3. How can you secure a Blazor WebAssembly app without using the Authorize attribute on every routable component?
> Add `@attribute [Authorize]` to _Imports.razor and make the login page `@attribute [AllowAnonymous]`.

4. What are some of the claims that are included in a JSON Web Token (JWT)?
> Issuer/ExpirationTime...
