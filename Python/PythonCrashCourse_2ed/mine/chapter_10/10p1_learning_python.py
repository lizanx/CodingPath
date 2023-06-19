# In order to use relative path, you must change the current working directory to here.
# Otherwise python cannot find the file "learning_python.txt"

# Version 1
with open("learning_python.txt") as file_object:
    content = file_object.read()
print(f"Version 1, read the entire file:\n{content}")

# Version 2
with open("learning_python.txt") as file_object:
    print("Version 2, loop over the file object:")
    for line in file_object:
        print(line, end='')

# Version 3
with open("learning_python.txt") as file_object:
    lines = file_object.readlines()
print("\nVersion 3, store lines in a list:")
for line in lines:
    print(line, end='')
