def city_country(name, country):
    return f"{name.title()}, {country.title()}"

s = city_country("Shenzhen", "china")
print(s)
s = city_country("London", "Britain")
print(s)
s = city_country("Ohio", "america")
print(s)