import json
import requests

response = requests.get(url='https://hacker-news.firebaseio.com/v0/item/19155826.json')
print(f'Status Code: {response.status_code}')

with open('data/readable_hn_data.json', 'w') as f:
    json.dump(response.json(), f, indent=4)
