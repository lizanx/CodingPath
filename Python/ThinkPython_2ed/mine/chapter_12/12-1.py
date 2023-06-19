def most_frequent(s):
    d = dict()
    for c in s:
        if c < 'A' or 'Z' < c < 'a' or c > 'z':
            continue
        if c.lower() not in d:
            d[c.lower()] = 1
        else:
            d[c.lower()] += 1
    l = []
    for k, v in d.items():
        l.append((v, k))
    l.sort(reverse=True)
    print(l)

if __name__ == '__main__':
    with open('words.txt') as fin:
        content = fin.read()
        most_frequent(content)