def is_sorted(l):
    if len(l) < 2:
        return True
    for i in range(len(l) - 1):
        if l[i] > l[i + 1]:
            return False
    return True

print(is_sorted([1, 2, 4]))
print(is_sorted(['b', 'a']))