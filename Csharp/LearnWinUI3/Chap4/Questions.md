1. How do DI and IoC relate?
> Dependency Injection is an implementation/type of Inverse of Control, there're others like service locator.

2. How do you navigate to the previous page in a WinUI application?
> Use `Frame.GoBack()`

3. What object do we use to manage dependencies?
> `IHost.Services` of type `IServiceProvider`

4. With Microsoft’s DI container, what method can you call to get an object instance?
> `GetService<T>` / `GetRequiredService<T>`

5. What is the name of the framework that queries objects in memory?
> LINQ

6. What event argument property can you access to get a parameter passed to another Page?
> `NavigationEventArgs.Parameter`

7. Which dictionary type is safe to use across threads?
> `ConcurrentDictionary<Tkey, Tvalue>`
