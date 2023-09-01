namespace Cooking.Data;

public class RecipeViewModel
{
    public required string Name { get; set; }
    public int TimeToCookMins { get; set; }
    public bool IsDeleted { get; set; }
    public required string Method { get; set; }
    public bool IsVegetarian { get; set; }
    public bool IsVegan { get; set; }
    public Recipe ToRecipe()
    {
        return new Recipe() {
            Name = this.Name,
            TimeToCook = new TimeSpan(this.TimeToCookMins / 60, this.TimeToCookMins % 60, 0),
            IsDeleted = false,
            Method = this.Method,
            IsVegetarian = this.IsVegetarian,
            IsVegan = this.IsVegan,
            Ingredients = new List<Ingredient>()
        };
    }
}
