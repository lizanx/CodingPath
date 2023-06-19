with open("guest_book.txt", "w") as file_object:
    while True:
        name = input("Please enter your name('quit' for quit): ")
        if name == 'quit':
            break
        greeting = f"Hello, {name.title()}. Welcome!"
        print(greeting)
        file_object.write(greeting + "\n")
