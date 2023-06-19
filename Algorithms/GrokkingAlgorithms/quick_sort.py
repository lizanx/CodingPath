import random

def quick_sort(array):
    if len(array) < 2:
        return array
    smaller, larger = [], []
    pivot = array[0]
    for i in range(1, len(array)):
        if array[i] < pivot:
            smaller.append(array[i])
        else:
            larger.append(array[i])
    return quick_sort(smaller) + [pivot] + quick_sort(larger)


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
        l = quick_sort(l)
        print('After quick sort:', l, '\n')