1. How can you replace a table with a templated component?
> Define a table-component which receives a `IEnumerable<TRow>` and a `RenderFragment` for displaying of each item as parameters.

2. How would you add default values for the Title property and the Body property of the Dialog component?
> Add default values after definition or in `OnInitialized`.

3. How can you determine which button was clicked when handling the @onclick event?
> Use a collection to store `ElementReference`s, use `@ref` to bind the reference to the button and pass the reference to handler.

4. Can you distribute your Dialog component using a NuGet package?
> Yes, you can publish it and upload it to NuGet.
