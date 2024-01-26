from itertools import product

l1 = [1, 2, 3]
l2 = [4, 5, 6]
l3 = [7, 8, 9]
for n1, n2, n3 in product(l1, l2, l3):
    print(n1, n2, n3)
