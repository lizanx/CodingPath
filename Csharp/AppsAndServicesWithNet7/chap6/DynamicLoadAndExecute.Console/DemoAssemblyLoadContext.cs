using System.Runtime.Loader;

internal class DemoAssemblyLoadContext : AssemblyLoadContext
{
    private AssemblyDependencyResolver _resolver;

    public DemoAssemblyLoadContext(string mainAssemblyToLoadPath)
        : base(isCollectible: true)
    {
        _resolver = new AssemblyDependencyResolver(mainAssemblyToLoadPath);
    }
}