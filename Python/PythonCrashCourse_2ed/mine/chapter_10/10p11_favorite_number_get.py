import json

try:
    with open("favorite_number.txt") as f:
        num = json.load(f)
except FileNotFoundError:
    print("It seems that we don't know your favorite number!")
else:
    print("I know your favorite number is " + num)