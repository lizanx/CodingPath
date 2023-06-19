class Restaurant:
    def __init__(self, name, cuisine):
        self.restaurant_name = name
        self.cuisine_type = cuisine
        self.number_served = 0
    def describe_restaurant(self):
        print(f"In {self.restaurant_name}, flavor offered: {self.cuisine_type}, "
            f"total served customers: {self.number_served}")
    def open_restaurant(self):
        print(f"{self.restaurant_name} is now open!")
    def set_number_served(self, num):
        if num <= self.number_served:
            print("Error! You can't decrease the number of served customers.")
        else:
            self.number_served = num
    def increment_number_served(self, num):
        if num < 0:
            print("Error! You can't decrease the number of served customers.")
        else:
            self.number_served += num

r = Restaurant("Hobbes' Bar", "wine and English foods")
r.describe_restaurant()
r.open_restaurant()

r.number_served = 2
r.describe_restaurant()

r.set_number_served(5)
r.describe_restaurant()

r.increment_number_served(3)
r.describe_restaurant()