def has_dumplicates(l):
    d = dict()
    for e in l:
        if e in d:
            return True
        d[e] = True
    return False


print(has_dumplicates([1, 2, 3, 2]))