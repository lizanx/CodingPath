namespace ContosoPizza.Data;

public static class Extensions
{
    public static void CreateDbIfNotExists(this IHost host)
    {
        using (var scope = host.Services.CreateScope())
        {
            PizzaContext context = scope.ServiceProvider.GetRequiredService<PizzaContext>()!;
            context.Database.EnsureCreated();
            DbInitializer.Initialize(context);
        }
    }
}
