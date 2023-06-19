class Restaurant:
    def __init__(self, name, cuisine):
        self.restaurant_name = name
        self.cuisine_type = cuisine
    def describe_restaurant(self):
        print(f"In {self.restaurant_name}, flavor offered: {self.cuisine_type}")
    def open_restaurant(self):
        print(f"{self.restaurant_name} is now open!")

r = Restaurant("Hobbes' Bar", "wine and English food")
r.describe_restaurant()

r = Restaurant("McDonald", "fast food")
r.describe_restaurant()

r = Restaurant("Ikea's Cafe", "northern European food")
r.describe_restaurant()
