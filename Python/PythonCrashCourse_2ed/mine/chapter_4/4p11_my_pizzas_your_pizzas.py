# 4-12 More Loops has the same solution as below
my_pizzas = ["Hawaii Flavor Pizza", "Roast Chicken Pizza", "Cheese Fruit Pizza"]
friend_pizzas = my_pizzas[:]

my_pizzas.append("Assorted Pizza")
friend_pizzas.append("Durian Pizza")

print("My favorite pizzas are:")
for pizza in my_pizzas:
    print(pizza)
print("My frientd's favorite pizzas are:")
for pizza in friend_pizzas:
    print(pizza)
