import requests
# import json
from plotly.graph_objs import Bar
from plotly import offline

url = 'https://api.github.com/search/repositories?q=language:python&sort=stars'
headers = {'Accept': 'application/vnd.github.v3+json'}
r = requests.get(url, headers)
print(f'Status code: {r.status_code}')
r_dict = r.json()
print(r_dict.keys())

print(f"Total repo counts: {r_dict['total_count']}")
repo_dicts = r_dict['items']

repo_links, stars, labels = [], [], []
for repo_dict in repo_dicts:
    repo_name = repo_dict['name']
    repo_url = repo_dict['html_url']
    repo_link = f"<a href='{repo_url}'>{repo_name}</a>"
    repo_links.append(repo_link)
    stars.append(int(repo_dict['stargazers_count']))
    owner = repo_dict['owner']['login']
    description = repo_dict['description']
    labels.append(f"{owner}<br />{description}")

# Visualization.
data = [
    {
        'type': "bar",
        'x': repo_links,
        'y': stars,
        'marker': {
            'color': 'rgb(60, 100, 150)',
            'line': {
                'width': 1.5,
                'color': 'rgb(25, 25, 25)',
            }
        },
        'opacity': 0.6,
        'hovertext': labels,
    }
]
my_layout = {
    'title': 'Most-Starred Python Projects on GitHub',
    'titlefont': {'size': 28},
    'xaxis': {
        'title': 'Repository',
        'titlefont': {'size': 24},
        'tickfont': {'size': 14},
    },
    'yaxis': {
        'title': 'Stars',
        'titlefont': {'size': 24},
        'tickfont': {'size': 14},
    },
}
fig = {'data': data, 'layout': my_layout}
offline.plot(fig, filename='data/python_repos.html')
