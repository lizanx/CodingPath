def middle(l):
    if len(l) < 2:
        return []
    return l[1:-1]

t = [1, 2, 3, 4]
print(middle(t))