from operator import itemgetter
import requests
from plotly.graph_objs import Bar
from plotly import offline

# https://github.com/HackerNews/API for api usage guide
response = requests.get(url='https://hacker-news.firebaseio.com/v0/beststories.json')
print(f'Status Code: {response.status_code}')

submission_ids = response.json()
# Limit the number of discussions to 20 to avoid long get time.
if len(submission_ids) > 20:
    submission_ids = submission_ids[:20]
# print(response.json())
# exit()
submission_dicts = []
for submission_id in submission_ids:
    url = f"https://hacker-news.firebaseio.com/v0/item/{submission_id}.json"
    r = requests.get(url)
    print(f'id:{submission_id} status_code:{r.status_code}')
    response_dict = r.json()
    # print(f'response: {response_dict}')
    submission_dicts.append({
        'title': response_dict['title'],
        'hn_link': f'http://news.ycombinator.com/item?id={submission_id}',
        'comments': response_dict['descendants'],
    })

submission_dicts = sorted(submission_dicts, key=itemgetter('comments'), reverse=True)
titles, comments, links = [], [], []
for submission_dict in submission_dicts:
    titles.append(f"<a href='{submission_dict['hn_link']}'>{submission_dict['title']}</a>")
    comments.append(int(submission_dict['comments']))
    links.append(submission_dict['hn_link'])

# Visualization.
data = [
    {
        'type': "bar",
        'x': titles,
        'y': comments,
        'marker': {
            'color': 'rgb(60, 100, 150)',
            'line': {
                'width': 1.5,
                'color': 'rgb(25, 25, 25)',
            }
        },
        'opacity': 0.6,
        'hovertext': titles,
    }
]
my_layout = {
    'title': 'Most Active Discussions on HN',
    'titlefont': {'size': 28},
    'xaxis': {
        'title': 'Discussion',
        'titlefont': {'size': 24},
        'tickfont': {'size': 14},
    },
    'yaxis': {
        'title': 'Comment',
        'titlefont': {'size': 24},
        'tickfont': {'size': 14},
    },
}
fig = {'data': data, 'layout': my_layout}
offline.plot(fig, filename='data/hn_discussions.html')
