def nested_sum(l):
    total = 0
    for e in l:
        if isinstance(e, list):
            total += sum(e)
        else:
            total += e
    return total

t = [[1, 2], [3], [4, 5, 6]]
print(nested_sum(t))