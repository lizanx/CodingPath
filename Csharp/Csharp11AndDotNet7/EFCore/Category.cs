using System.ComponentModel.DataAnnotations.Schema;

namespace Packt.Shared;

public class Category
{
    public int CategoryId { get; set; }
    public string? CategoryName { get; set; }
    [Column(TypeName = "ntext")]
    public string? Description { get; set; }
    // A navigation property for related rows.
    public virtual ICollection<Product> Products { get; set; }

    public Category()
    {
        // to enable developers to add products to a Category, we must
        // initialize the navigation property to an empty collection
        Products = new HashSet<Product>();
    }
}