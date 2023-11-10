1. Assembly Metadata and Manifest + Type Metadata + IL Code + Resource(optional)
2. Assembly/Class/Method/Member
3. Major.Minor.Patch:
    - Major change may contain breaking changes
    - Minor change contains new feature or bug fix
    - Patch change contains bug fix
4. `Assembly.GetEntryAssembly()`
5. `assembly.GetCustomAttributes()`
6. Inherit from the `Attribute` class.
7. `AssemblyLoadContext`
8. A tree representation of codes as structure that you can examine or execute.
9. Source generators allow programmers to get a compilation object that represents all the code  
being compiled, and then dynamically generate additional code files, and compile those too.
10. `ISourceGenerator` interface, `Execute`/`Initialize` methods.
