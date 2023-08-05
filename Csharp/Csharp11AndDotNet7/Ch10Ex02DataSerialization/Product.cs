using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using Microsoft.EntityFrameworkCore;

namespace Packt.Shared;

class Product
{
    [Required]
    public int ProductId { get; set; }
    [Required]
    [StringLength(40)]
    public string ProductName { get; set; } = null!;
    [Column(TypeName = "money")]
    public decimal? UnitPrice { get; set; }
    [Column("UnitsInStock", TypeName = "smallint")]
    public int? Stock { get; set; }
    [Column(TypeName = "bit")]
    public bool Discontinued { get; set; }
    public int CategoryId { get; set; }

    public Product() {}
}