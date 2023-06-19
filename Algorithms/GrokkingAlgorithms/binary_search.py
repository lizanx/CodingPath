import random

def generate_sorted_list(size):
    if size <= 0:
        return None
    cnt = 0
    l = []
    while cnt < size:
        l.append(random.randint(0, size * 2))
        cnt += 1
    l = list(set(l))
    l.sort()
    return l


def binary_search(l, target):
    # print('In', l, 'search for', target)
    left = 0
    right = len(l) - 1
    while left <= right:
        mid = int((left + right) / 2)
        # print(left, right, mid, l[mid])
        if l[mid] == target:
            return mid
        elif l[mid] < target:
            left = mid + 1
        else:
            right = mid - 1
    return None

if __name__ == '__main__':
    i = 0
    while i < 3:
        size = random.randint(5, 10)
        l = generate_sorted_list(size)
        print('Original list:', l)
        target_index = random.randint(0, len(l) - 1)
        target = l[target_index]
        print('Target_index:', target_index, ' target:', target)
        res = binary_search(l, target)
        print('Result:', res, '\n')
        i += 1