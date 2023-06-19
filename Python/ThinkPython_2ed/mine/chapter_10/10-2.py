def cumsum(l):
    res = []
    for i in range(len(l)):
        res.append(sum(l[:i + 1]))
    return res

t = [1, 2, 3]
print(cumsum(t))