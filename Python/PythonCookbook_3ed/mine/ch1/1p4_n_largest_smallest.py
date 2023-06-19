import heapq
from random import randint

data = [randint(-100, 100) for x in range(0, 20)]
n = 3

print(f'data: {data}\nsorted:{sorted(data)}')

print('--By sorted--')
print(f'{n} largest: {sorted(data)[-3:]}')
print(f'{n} smallest: {sorted(data)[0:3]}')

print('--By heapq--')
print(f'{n} largest: {heapq.nlargest(n, data)}')
print(f'{n} smallest: {heapq.nsmallest(n, data)}')
print('\n\n')

portfolio = [
    {'name': 'IBM', 'shares': 100, 'price': 91.1},
    {'name': 'AAPL', 'shares': 50, 'price': 543.22},
    {'name': 'FB', 'shares': 200, 'price': 21.09},
    {'name': 'HPQ', 'shares': 35, 'price': 31.75},
    {'name': 'YHOO', 'shares': 45, 'price': 16.35},
    {'name': 'ACME', 'shares': 75, 'price': 115.65}
]
print(f'portfolio: {portfolio}')

print('--By sorted--')
print(f'{n} largest: {sorted(portfolio, key=lambda pf: pf["price"])[-3:]}')
print(f'{n} smallest: {sorted(portfolio, key=lambda pf: pf["price"])[0:3]}')

print('--By heapq--')
print(f'{n} largest: {heapq.nlargest(n, portfolio, key=lambda pf: pf["price"])}')
print(f'{n} smallest: {heapq.nsmallest(n, portfolio, key=lambda pf: pf["price"])}')
print('\n\n')

