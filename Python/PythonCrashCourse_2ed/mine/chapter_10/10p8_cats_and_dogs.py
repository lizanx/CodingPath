f1 = "cats.txt"
f2 = "dogs.txt"
try:
    with open(f1) as f:
        content = f.read()
except FileNotFoundError:
    print(f"File {f1} is not found, skip it.")
else:
    print("File-1:\n" + content + "\n")

try:
    with open(f2) as f:
        content = f.read()
except FileNotFoundError:
    print(f"File {f2} is not found, skip it.")
else:
    print("File-2:\n" + content + "\n")
