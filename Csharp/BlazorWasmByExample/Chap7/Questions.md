1. Can localStorage be used to maintain the cart’s state when the page is reloaded?
> Yes, local storage won't be cleared when reloading a page.

2. Why don’t we need to call the StateHasChanged method in the Store component?
> Because Blazor automatically detects the DOM change and update the rendering for us.

3. How would you update the cart to allow for the addition of more than one of each type of product at a time?
> Define a new model 'Order' to include both type and quantity.

4. When using DI, what is the difference between the various service lifetimes?
> 1. Singleton: The class instance is only created once and all required service is the same one.
> 2. Scope: In general SSR case, each HTTP request corresponds to a scope. In BlazorServer, each connection(SignalR) to a user 
corresponds to a scope. In BlazorWasm, scope is the same as singleton.
> 3. Transient: The required service is created each time asked, and it's out of DI's control.
