import json

num = input("Enter your favorite number: ")
with open("favorite_number.txt", "w") as f:
    json.dump(num, f)
