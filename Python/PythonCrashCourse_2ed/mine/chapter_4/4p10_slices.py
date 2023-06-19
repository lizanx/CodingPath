cubes = [n ** 3 for n in range(1, 11)]

print("The first three numbers are:")
for n in cubes[:3]:
    print(n)

print("Three items from the middle of the list are:")
for n in cubes[5:8]:
    print(n)

print("The last three items in the list are:")
for n in cubes[-3:]:
    print(n)