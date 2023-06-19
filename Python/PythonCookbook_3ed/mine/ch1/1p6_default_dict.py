from collections import defaultdict

d = defaultdict(int) # each value is initialized as 0 by default
name = 'hello,world!'
for char in name:
    d[char] += 1
for key, value in d.items():
    print(f'{key}: {value}')

d2 = dict()
d2.setdefault('a', []).append('hi')
d2.setdefault('a', []).append('python')
d2.setdefault('c', []).append('C++')
for key, value in d2.items():
    print(f'\t{key}: {value}')
