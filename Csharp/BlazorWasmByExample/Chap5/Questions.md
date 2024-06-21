1. Can IJSRuntime be used to render a UI?
> No, the rendering is controlled by BlazorComponents(there's a virtual DOM). 
You should never manipulate DOM directly in JS, which may cause clashes or out of sync.

2. How would you add our local storage service to a Razor class library?
> Create a new razor-class-lib and reference it from other projects.

3. What are the benefits of using a collocated JavaScript file?
> Separation concerns: extract the js codes used only in one razor component 
to avoid clutter the global js codes.

4. Do you think that you will still use JavaScript? If so, what will you use it for?
> Yes, for some specific browser APIs that are only accessible via JavaScript.

5. In what scenarios do you need to invoke JavaScript asynchronously rather than synchronously?
> Long-running tasks, inside-initialization tasks.
