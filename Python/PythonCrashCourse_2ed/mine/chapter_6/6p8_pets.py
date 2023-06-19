dog = {'kind': 'labrador', 'owner': 'Mary'}
cat = {'kind': 'persian', 'owner': 'Jane'}
pets = [dog, cat]
for pet in pets:
    print(f"Kind of the pet: {pet['kind']}, owner: {pet['owner']}")