using System.ComponentModel.DataAnnotations;
using Microsoft.EntityFrameworkCore;

namespace Packt.Shared;

class Category
{
    [Required]
    public int CategoryId { get; set; }
    [Required]
    [StringLength(15)]
    public string CategoryName { get; set; } = null!;
    public string? Description { get; set; }

    public virtual ICollection<Product>? Products { get; set; }

    public Category()
    {
        Products = new HashSet<Product>();
    }
}