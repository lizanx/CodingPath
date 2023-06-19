import random

def choose_from_hist(l):
    i = random.randint(1, len(l))
    return l[i - 1]

if __name__ == '__main__':
    l = []
    data = ['a', 'b', 'b', 'c', 'd', 'a', 'a']
    for i in range(10000):
        l.append(choose_from_hist(data))
    print(f"a: {l.count('a')}, b: {l.count('b')}, c: {l.count('c')}, d: {l.count('d')}")