import random

def merge(a1, a2):
    res = []
    while len(a1) > 0 and len(a2) > 0:
        if a1[0] < a2[0]:
            res.append(a1.pop(0))
        else:
            res.append(a2.pop(0))
    if a1:
        res.extend(a1)
    if a2:
        res.extend(a2)
    return res

def merge_sort(array):
    if len(array) < 2:
        return array
    return merge(merge_sort(array[:len(array)//2]), merge_sort(array[len(array)//2:]))

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
        l = merge_sort(l)
        print('After merge sort:', l, '\n')