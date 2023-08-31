using Cooking.Data;
using Microsoft.EntityFrameworkCore;

namespace Cooking.Services;

public class RecipeService
{
    readonly AppDbContext _context;
    readonly ILogger _logger;

    public RecipeService(AppDbContext context, ILoggerFactory factory)
    {
        _context = context;
        _logger = factory.CreateLogger<RecipeService>();
    }

    public async Task<Recipe?> GetRecipe(int id)
    {
        return await _context.Recipes
            .Where(it => !it.IsDeleted && it.RecipeId == id)
            .SingleOrDefaultAsync();
    }
    public async Task<int> CreateRecipeAsync(Recipe recipe)
    {
        _context.Add(recipe);
        await _context.SaveChangesAsync();
        return recipe.RecipeId;
    }
}