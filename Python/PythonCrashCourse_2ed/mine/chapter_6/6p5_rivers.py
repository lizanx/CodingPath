rivers = {
    'nile': 'Egypt',
    'yellow': 'China',
    'rhine': 'England',
}

for river, country in rivers.items():
    print(f"{river.title()} flows through {country.title()}")

print("\nAll the rivers:")
for river in rivers:
    print(river)

print("\nAll the countries:")
for country in rivers.values():
    print(country)