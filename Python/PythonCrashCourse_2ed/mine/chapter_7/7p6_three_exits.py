pizza_toppings = []

# Version 1
print("Version 1:")
topping = ""
while topping != "quit":
    topping = input("Please enter the pizza topping you like:"
        "(enter 'quit' to stop) ")
    if topping != "quit":
        pizza_toppings.append(topping)
        print(f"We will add {topping} for you.")

# Version 2
print("\nVersion 2:")
flag = True
while flag:
    topping = input("Please enter the pizza topping you like:"
        "(enter 'quit' to stop) ")
    if topping != "quit":
        pizza_toppings.append(topping)
        print(f"We will add {topping} for you.")
    else:
        flag = False

# Version 3
print("\nVersion 3:")
while True:
    topping = input("Please enter the pizza topping you like:"
        "(enter 'quit' to stop) ")
    if topping == "quit":
        break
    else:
        pizza_toppings.append(topping)
        print(f"We will add {topping} for you.")