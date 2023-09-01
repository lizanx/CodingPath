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

    public async Task<List<RecipeViewModel>> GetRecipes()
    {
        return await _context.Recipes.Where( r => !r.IsDeleted )
            .Select(r => new RecipeViewModel {
                Name = r.Name,
                TimeToCookMins = (int)r.TimeToCook.TotalMinutes,
                IsDeleted = r.IsDeleted,
                Method = r.Method,
                IsVegetarian = r.IsVegetarian,
                IsVegan = r.IsVegan
            })
            .ToListAsync();
    }
    public async Task<RecipeViewModel?> GetRecipe(int id)
    {
        var recipe = await _context.Recipes
            .Where(it => !it.IsDeleted && it.RecipeId == id)
            .SingleOrDefaultAsync();
        return recipe is null
            ? null
            : new RecipeViewModel
            {
                Name = recipe.Name,
                TimeToCookMins = (int)recipe.TimeToCook.TotalMinutes,
                IsDeleted = recipe.IsDeleted,
                Method = recipe.Method,
                IsVegetarian = recipe.IsVegetarian,
                IsVegan = recipe.IsVegan
            };
    }
    public async Task<int> CreateRecipeAsync(RecipeViewModel rvm)
    {
        var recipe = rvm.ToRecipe();
        _context.Add(recipe);
        await _context.SaveChangesAsync();
        return recipe.RecipeId;
    }
    public async Task<int> UpdateRecipeAsync(RecipeViewModel rvm, int id)
    {
        var recipe = await _context.Recipes.FindAsync(id) ?? throw new Exception("Recipe not found.");
        if (recipe.IsDeleted) throw new Exception("Couldn't update a deleted recipe.");
        recipe.Name = rvm.Name;
        recipe.TimeToCook = new TimeSpan(rvm.TimeToCookMins / 60, rvm.TimeToCookMins % 60, 0);
        recipe.Method = rvm.Method;
        recipe.IsVegetarian = rvm.IsVegetarian;
        recipe.IsVegan = rvm.IsVegan;
        await _context.SaveChangesAsync();
        return recipe.RecipeId;
    }
    public async Task DeleteRecipeAsync(int id)
    {
        var recipe = await _context.Recipes.FindAsync(id) ?? throw new Exception("Recipe not found.");
        if (recipe.IsDeleted) throw new Exception("Cannot delete a non-existed Recipe.");
        recipe.IsDeleted = true;
        await _context.SaveChangesAsync();
    }
}