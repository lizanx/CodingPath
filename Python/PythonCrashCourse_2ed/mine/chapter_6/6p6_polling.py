favorite_languages = {
    'jen': 'python',
    'sarah': 'c',
    'edward': 'ruby',
    'phil': 'python',
    }
poll_list = ['Jen', 'Edward', 'Bruce', 'Mary']

for person in poll_list:
    if person.lower() in favorite_languages.keys():
        print(f"{person.title()}, thank you for voting for your favorite language {favorite_languages[person.lower()].title()}!")
    else:
        print(f"{person.title()}, we sincerely invite you to vote for your favorite language!")