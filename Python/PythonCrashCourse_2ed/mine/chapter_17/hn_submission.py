from operator import itemgetter
import requests

response = requests.get(url='https://hacker-news.firebaseio.com/v0/item/19155826.json')
print(f'Status Code: {response.status_code}')

submission_ids = response.json()
submission_dicts = []
for submission_id in submission_ids:
    url = f"https://hacker-news.firebaseio.com/v0/item/{submission_id}.json"
    r = requests.get(url)
    print(f'id:{submission_id} status_code:{r.status_code}')
    response_dict = r.json()
    print(f'response: {response_dict}')
    submission_dicts.append({
        'title': response_dict['title'],
        'hn_link': f'http://news.ycombinator.com/item?id={submission_id}',
        'comments': response_dict['descendants'],
    })

submission_dicts = sorted(submission_dicts, key=itemgetter('comments'), reverse=True)
for submission_dict in submission_dicts:
    print(f"\nTitle: {submission_dict['title']}")
    print(f"Discussion link: {submission_dict['hn_link']}")
    print(f"Comments: {submission_dict['comments']}")
