with open("reasons", "a") as file_object:
    while True:
        reason = input("Please give a reason why you like programming('quit' for quit): ")
        if reason == 'quit':
            break
        file_object.write(reason + "\n")