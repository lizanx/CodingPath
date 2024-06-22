using ShoppingCart.Models;

namespace ShoppingCart.Services;

class CartService : ICartService
{
    private List<Product> _cart = [];
    private int _total;

    public IList<Product> Cart
    {
        get => _cart;
    }

    public int Total
    {
        get => _total;
    }

    public event Action? OnChange;

    public void AddProduct(Product product)
    {
        _total += product.Price;
        _cart.Add(product);
        NotifyStateChanged();
    }

    public void DeleteProduct(Product product)
    {
        _total -= product.Price;
        _cart.Remove(product);
        NotifyStateChanged();
    }

    private void NotifyStateChanged() =>
        OnChange?.Invoke();
}
