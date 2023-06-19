current_users = ["Jane", "George", "Koby", "John", "Diana"]
new_users = ["john", "jane", "Peter", "Harry", "Bruce"]

for new_user in new_users:
    if new_user.lower() in [user.lower() for user in current_users]:
        print(f"Username '{new_user}' has been used, please change to a new one!")
    else:
        print(f"Username '{new_user}' is available!")
