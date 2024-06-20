1. Can Razor components include JavaScript?
> Yes, you can inject `IJSRuntime` for interops with JS.

2. What types of loops are supported by Razor syntax?
> `for`, `foreach`, `while`, `do {} while` -- basically all loop styles in C#.

3. Can the parameter of a component be defined using a POCO?
> Yes, even complex classes are supported.

4. Will Hot Reload render changes to CSS files?
> No, it mainly works for C# codes changes.

5. How can a child component trigger an infinite loop?
> If it renders its parent(or ancestor) component.
