with open("guests.txt", "w") as file_object:
    while True:
        name = input("Please enter your name('quit' for quit): ")
        if name == 'quit':
            break
        file_object.write(name.title() + "\n")
