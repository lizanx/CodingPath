import random

def index_of_smallest(l):
    if not len(l):
        return None
    smallest = l[0]
    record = 0
    for i in range(0, len(l)):
        if l[i] < smallest:
            record = i
            smallest = l[i]
    return record

def selection_sort(l):
    res = []
    while l:
        i = index_of_smallest(l)
        res.append(l[i])
        del l[i]
    return res

def generate_list(size):
    if size <= 0:
        return None
    cnt = 0
    l = []
    while cnt < size:
        l.append(random.randint(0, size * 2))
        cnt += 1
    return l


if __name__ == '__main__':
    for i in range(0, 3):
        l = generate_list(10)
        print('Original list:', l)
        l = selection_sort(l)
        print('After selection sort:', l, '\n')