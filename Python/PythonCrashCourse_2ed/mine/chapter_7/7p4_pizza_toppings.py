pizza_toppings = []
while True:
    topping = input("Please enter the pizza topping you like:"
        "(enter 'quit' to stop) ")
    if topping == "quit":
        break
    else:
        pizza_toppings.append(topping)
        print(f"We will add {topping} for you.")