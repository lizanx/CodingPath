def in_bisect(l, word, start):
    if len(l) <= 2:
        if word in l:
            return l.index(word) + start
        return None
    n = in_bisect(l[:int(len(l) / 2)], word, start)
    if n:
        return n
    return in_bisect(l[int(len(l) / 2):], word, start + int(len(l) / 2))


if __name__ == '__main__':
    content = []
    with open("words.txt") as fin:
        for word in fin:
            content.append(word.strip())
        # content = fin.readlines()
        print("index =", in_bisect(content, 'pampero', 0))
    print("index =", in_bisect(['absolute', 'definite', 'fine', 'yellow'], 'fine', 0))