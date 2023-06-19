import requests
import json

url = 'https://api.github.com/search/repositories?q=language:python&sort=stars'
headers = {'Accept': 'application/vnd.github.v3+json'}
r = requests.get(url, headers)
print(f'Status code: {r.status_code}')
r_dict = r.json()
print(r_dict.keys())

print(f"Total repo counts: {r_dict['total_count']}")
repo_dicts = r_dict['items']
print(f"{len(repo_dicts)} repos found.")
repo_dict = repo_dicts[0]
print(f"Keys: {len(repo_dict.keys())}")
for key in repo_dict.keys():
    print(key)


with open("data/tmp.json", "w") as f:
    json.dump(r_dict, f, indent=4)
