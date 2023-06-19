import csv
from plotly.graph_objs import Scattergeo, Layout
from plotly import offline


longs, lats, brights = [], [], []

with open("data/world_fires_7_day.csv") as f:
    fire_data = csv.reader(f)
    header = next(fire_data)
    print(header)

    for line in fire_data:
        longs.append(float(line[header.index('longitude')]))
        lats.append(float(line[header.index('latitude')]))
        brights.append(float(line[header.index('bright_ti4')]))
# print(longs)
# print(lats)
# print(brights)
data = [
    {
        'type': 'scattergeo',
        'lon': longs,
        'lat': lats,
        # 'text': hover_texts,
        'marker': {
            'size': [bright/100 for bright in brights],
            'color': brights,
            'colorscale': 'Viridis',
            'reversescale':True,
            'colorbar': {'title': 'Brightness'},
        },
    },
]
my_layout = Layout(title='World Fires Distribution')
fig = {'data': data, 'layout': my_layout}
offline.plot(fig, filename='world_fires.html')
