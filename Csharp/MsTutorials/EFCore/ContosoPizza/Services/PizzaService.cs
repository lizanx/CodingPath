using ContosoPizza.Models;
using ContosoPizza.Data;
using Microsoft.EntityFrameworkCore;

namespace ContosoPizza.Services;

public class PizzaService(PizzaContext db)
{
    private readonly PizzaContext _db = db;

    public IEnumerable<Pizza> GetAll() =>
        _db.Pizzas.AsNoTracking().ToList();

    public Pizza? GetById(int id) =>
        _db.Pizzas
            .Include(p => p.Toppings)
            .Include(p => p.Sauce)
            .AsNoTracking()
            .SingleOrDefault();

    public Pizza? Create(Pizza newPizza)
    {
        _db.Pizzas.Add(newPizza);
        _db.SaveChanges();
        return newPizza;
    }

    public void AddTopping(int PizzaId, int ToppingId)
    {
        if (_db.Pizzas.Find(PizzaId) is Pizza pizzaToUpdate
            && _db.Toppings.Find(ToppingId) is Topping toppingToUpdate)
        {
            pizzaToUpdate.Toppings ??= new List<Topping>();
            pizzaToUpdate.Toppings.Add(toppingToUpdate);

            _db.SaveChanges();
        }
        else
        {
            throw new InvalidOperationException("Pizza or topping doesn't exist");
        }
    }

    public void UpdateSauce(int PizzaId, int SauceId)
    {
        if (_db.Pizzas.Find(PizzaId) is Pizza pizzaToUpdate
            && _db.Sauces.Find(SauceId) is Sauce sauceToUpdate)
        {
            pizzaToUpdate.Sauce = sauceToUpdate;
            _db.SaveChanges();
        }
        else
        {
            throw new InvalidOperationException("Pizza or sauce doesn't exist");
        }
    }

    public void DeleteById(int id)
    {
        if (_db.Pizzas.Find(id) is Pizza pizzaToDelete)
        {
            _db.Pizzas.Remove(pizzaToDelete);
            _db.SaveChanges();
        }
    }
}