car = "Nissan"
print("Is car == 'Benz'? I predict False")
print(car == "Benz")

cell_phone = "OnePlus"
print("\nIs cell_phone == 'OnePlus'? I predict True")
print(cell_phone == 'OnePlus')

cell_phone = "OnePlus"
print("\nIs cell_phone of brand 'oneplus'? I predict True")
print(cell_phone.lower() == 'oneplus')

print("1 == 2?", 1 == 2, "\t2 != 3?", 2 != 3, "\t3 >= 4?", 3 >= 4, "\t 4 <= 5?", 4 <= 5)

print("1 is odd and 2 is even?", 1 % 2 == 1 and 2 % 2 == 0)
print("1 > 3 or 2 > 3?", 1 > 3 or 2 > 3)

l = ["Nissan", "Benz", "BMW", "Audi", "Honda", "Toyota"]
print("Is car is list l?", car in l)
print("Ferrari not in list l?", "Ferrari" not in l)
