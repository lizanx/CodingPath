def chop(l):
    if len(l) >= 2:
        del l[0]
        del l[-1]
    else:
        l = []

t = [1, 2, 3, 4]
chop(t)
print(t)