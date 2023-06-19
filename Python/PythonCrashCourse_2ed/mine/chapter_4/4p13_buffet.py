foods = ("bread", "sandwich", "coffee", "salad", "dissert")

print("The food offered by this buffet includes:")
for food in foods:
    print(food)

# The below line will cause error.
# foods[0] = "cake"

foods = ("cake", "hamburger", "coffee", "salad", "dissert")
print("\nThe new kinds of food offered include:")
for food in foods:
    print(food)
