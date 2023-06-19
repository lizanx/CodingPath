favorite_places = {'gavin': ['vancouver', 'melbourne', 'Belgium'],
    'diana': ['amazon', 'america'],
    'thor': ['asgard', 'earth', 'universe'],
    }
for person, places in favorite_places.items():
    if len(places) > 1:
        print(f"The favorite places of {person} are: {places}")
    else:
        print(f"The favorite place of {person} is {places[0]}")