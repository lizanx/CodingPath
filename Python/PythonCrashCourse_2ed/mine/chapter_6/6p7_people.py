miss_cui = {
    'first name': 'yifeng',
    'last name': 'cui',
    'city': 'Yingshang',
    'age': 28,
}
miss_jiang = {
    'first name': 'wanyang',
    'last name': 'jiang',
    'city': 'Yingshang',
    'age': 28,
}
mr_xu = {
    'first name': 'yu',
    'last name': 'xu',
    'city': 'Hefei',
    'age': 26,
}
people = [miss_cui, miss_jiang, mr_xu]
for person in people:
    print(f"name: {person['last name'].title()}{person['first name'].title()}, live in {person['city']}, {person['age']} years old")