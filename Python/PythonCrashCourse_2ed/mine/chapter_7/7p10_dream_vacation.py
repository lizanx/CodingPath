vacations = []
while True:
    place = input("If you could visit one place in the world, where would you go?(Enter 'quit' to exit): ")
    if place == 'quit':
        break
    vacations.append(place)
print(vacations)