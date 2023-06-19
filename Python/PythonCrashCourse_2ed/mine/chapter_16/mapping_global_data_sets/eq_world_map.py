import json
from plotly.graph_objs import Scattergeo, Layout
from plotly import offline
from plotly import colors
from random import choice


filename = "data/eq_data_30_day_m1.json"
with open(filename) as f:
    all_eq_data = json.load(f)

all_eq_dicts = all_eq_data['features']
# Extract data.
mags, lons, lats, hover_texts = [], [], [], []
for eq_dict in all_eq_dicts:
    mags.append(eq_dict['properties']['mag'])
    lons.append(eq_dict['geometry']['coordinates'][0])
    lats.append(eq_dict['geometry']['coordinates'][1])
    hover_texts.append(eq_dict['properties']['title'])

# Randomly choose a collorscale.
colorscales = []
for cs in colors.PLOTLY_SCALES.keys():
    colorscales.append(cs)
colorscale = choice(colorscales)
# Map the earthquakes.
data = [
    {
        'type': 'scattergeo',
        'lon': lons,
        'lat': lats,
        'text': hover_texts,
        'marker': {
            'size': [2*mag for mag in mags],
            'color': mags,
            # 'colorscale': 'Viridis',
            'colorscale': colorscale,
            'reversescale':True,
            'colorbar': {'title': 'Magnitude'},
        },
    },
]
my_layout = Layout(title=all_eq_data['metadata']['title'])
fig = {'data': data, 'layout': my_layout}
offline.plot(fig, filename='global_earthquakes.html')
