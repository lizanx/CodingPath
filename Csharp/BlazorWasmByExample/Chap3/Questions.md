1. How would you rewrite the Guess the Number game to use a custom error component?
> Write a custom error-handling component with a `RenderFragment` child and offers an error-handling method.
Pass the component itself or the handling method as `CascadingParameter`.
Then add the `CascadingParameter` to its child components and use it to handle errors.

2. What types of applications benefit the most from AOT?
> Computation-intensive applications.

3. What are the different log levels and when should you use each one?
> `Trace`: extremely verbose, always disabled for production.
`Debug`: especially for development usage.
`Information`: log important messages in normal execution.
`Warn`: something not normal happend.
`Error`: something failed, but it can be recovered.
`Critical`: something extremely bad happened and the app cannot recover.

4. How do you debug a Blazor WebAssembly app in the browser?
> Run in debug mode, SHIFT+ALT+D in browser to enter debug mode, navigate to *Source* tab.

5. Can you deploy a Blazor WebAssembly app to Microsoft Azure for free?
> Yes, there's a free plan you can choose.
