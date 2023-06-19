cities = {
    'Shenzhen': {'country': 'China', 'population': 12530000, 'fact': "one of China's biggest cities"},
    'New York': {'country': "America", 'polulation': 7610000, 'fact': 'capital of America'},
    'Manchester': {'country': 'England', 'population': 510000, 'fact': 'a movie with the same name is great'},
}
for city, info in cities.items():
    print(f"About {city}:")
    for key,val in info.items():
        print(f"\t{key}: {val}")
    print()