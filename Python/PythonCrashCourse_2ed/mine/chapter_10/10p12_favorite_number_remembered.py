import json

def get_stored_fav_num(file_name):
    try:
        with open(file_name) as f:
            num = json.load(f)
    except FileNotFoundError:
        # print("It seems that we don't know your favorite number!")
        return None
    else:
        print("I know your favorite number is " + num)
        return int(num)


def store_fav_num(file_name):
    num = input("Enter your favorite number: ")
    with open(file_name, "w") as f:
        json.dump(num, f)


file_name = "favorite_number.txt"
if get_stored_fav_num(file_name):
    pass
else:
    store_fav_num(file_name)