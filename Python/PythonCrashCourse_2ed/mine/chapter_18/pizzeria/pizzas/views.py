from django.shortcuts import render

from pizzas.models import Pizza, Topping

from .models import Pizza, Topping

# Create your views here.
def index(request):
    """The home page for pizzas."""
    return render(request, 'pizzas/index.html')

def pizzas(request):
    """All pizzas."""
    pizzas = Pizza.objects.order_by('name')
    context = {'pizzas': pizzas}
    return render(request, 'pizzas/pizzas.html', context)

def pizza(request, pizza_name):
    """Show toppings of a pizza."""
    pizza = Pizza.objects.get(name=pizza_name)
    toppings = pizza.topping_set.order_by('name')
    context = {'pizza': pizza, 'toppings': toppings}
    return render(request, 'pizzas/pizza.html', context)
