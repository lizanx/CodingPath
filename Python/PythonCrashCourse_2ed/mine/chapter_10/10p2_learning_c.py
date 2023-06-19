with open("learning_python.txt") as file_object:
    for line in file_object:
        print(line.replace("Python", "C"), end='')