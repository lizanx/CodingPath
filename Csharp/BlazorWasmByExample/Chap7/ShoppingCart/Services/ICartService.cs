using ShoppingCart.Models;

namespace ShoppingCart.Services;

interface ICartService
{
    IList<Product> Cart { get; }
    int Total { get; }
    event Action OnChange;
    void AddProduct(Product product);
    void DeleteProduct(Product product);
}
