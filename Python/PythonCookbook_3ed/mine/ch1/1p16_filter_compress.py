from itertools import compress

mylist = [1, 4, -5, 10, -7, 2, 3, -1]

positivelist = [n for n in mylist if n > 0]
print(f'positivelist:\t{positivelist}')

abslist = [n if n >= 0 else -n for n in mylist]
abslist2 = list((n if n >= 0 else -n for n in mylist))
print(f'adbslist:\t{abslist}\nabslist2:\t{abslist2}')

values = ['1', '2', '-3', '-', '4', 'N/A', '5']
def is_int(val) -> bool:
    try:
        intval = int(val)
        return True
    except ValueError:
        return False
ints = list(filter(is_int, values))
print(f'ints:\t{ints}')

addresses = [
    '5412 N CLARK',
    '5148 N CLARK',
    '5800 E 58TH',
    '2122 N CLARK',
    '5645 N RAVENSWOOD',
    '1060 W ADDISON',
    '4801 N BROADWAY',
    '1039 W GRANVILLE',
]
counts = [ 0, 3, 10, 4, 1, 7, 6, 1]
greater_than_5 = [n > 5 for n in counts]
print(list(compress(addresses, greater_than_5)))