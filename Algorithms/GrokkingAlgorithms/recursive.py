def recursive_sum(l):
    return 0 if len(l) == 0 else l[0] + recursive_sum(l[1:])

def recursive_count(l):
    return 0 if len(l) == 0 else 1 + recursive_count(l[1:])

def recursive_max(l):
    if len(l) == 1:
        return l[0]
    submax = recursive_max(l[1:])
    return l[0] if l[0] > submax else submax


if __name__ == '__main__':
    l = [7, 4, 9, 10, 5]
    print(recursive_sum(l), recursive_count(l), recursive_max(l))