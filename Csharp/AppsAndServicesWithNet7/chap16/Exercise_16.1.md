1. Client/Server/Hybrid:
    - Blazor Wasm: Download the runtime to client and run in the browser
    - Blazor Server: UI updates are handled by server via SignalR
    - Blazor Hybrid: Server first before Wasm is downloaded, then switch to Wasm
2. No, due to the limitations of browsers, some APIs are unavailable.
3. `.razor`
4. Declare it in App.razor.
5. Use `@page "routing"` directive.
6. When you don't want sub-pages to match.
7. This file applies to razor files only, you need to import namespaces separately in code-behind cs files.
8. Use attribute `[SupplyParameterFromQuery(Name="")]`
9. A grid layout offered by Microsoft.
10. Through javascript inter-opration.
