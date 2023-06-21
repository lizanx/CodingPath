from operator import itemgetter

rows = [
    {'fname': 'Brian', 'lname': 'Jones', 'uid': 1003},
    {'fname': 'David', 'lname': 'Beazley', 'uid': 1002},
    {'fname': 'John', 'lname': 'Cleese', 'uid': 1001},
    {'fname': 'Big', 'lname': 'Jones', 'uid': 1004}
]

by_uid = sorted(rows, key=itemgetter('uid'))
print(f'sort by uid:')
for item in by_uid:
    print(f'\t{item}')
print()

by_lname_uid = sorted(rows, key=itemgetter('lname', 'uid'))
print(f'sort by lname then by uid:')
for item in by_lname_uid:
    print(f'\t{item}')

by_lname_uid_2 = sorted(rows, key=lambda item: (item['lname'], item['uid']))
print(f'sort by lname then by uid:(lambda)')
for item in by_lname_uid:
    print(f'\t{item}')
