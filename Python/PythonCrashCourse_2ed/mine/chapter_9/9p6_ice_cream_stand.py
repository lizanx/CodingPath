class Restaurant:
    def __init__(self, name, cuisine):
        self.restaurant_name = name
        self.cuisine_type = cuisine
    def describe_restaurant(self):
        print(f"In {self.restaurant_name}, flavor offered: {self.cuisine_type}")
    def open_restaurant(self):
        print(f"{self.restaurant_name} is now open!")

class IceCreamStand(Restaurant):
    def __init__(self, name, cuisine, flavors):
        super().__init__(name, cuisine)
        self.flavors = flavors
    def show_all_flavors(self):
        print("All the flavors offered:")
        for flavor in self.flavors:
            print(f"\t{flavor}")

ics = IceCreamStand("McDonald's Dissert", "ice cream", ["strawberry", "vanilla", "cherry"])
ics.show_all_flavors()