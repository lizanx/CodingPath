def make_sandwich(*ingredients):
    print("The sandwich you order includes:")
    for ingredient in ingredients:
        print(f"\t{ingredient}")

make_sandwich("egg", "hotdog")
make_sandwich("salad", "ketchup", "beef")
make_sandwich("cheese", "lettuce", "onion", "chicken")