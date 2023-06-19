def has_dumplicates(l):
    for e in l:
        if l.count(e) > 1:
            return True
    return False


print(has_dumplicates([1, 2, 3, 2]))