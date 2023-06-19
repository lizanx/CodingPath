import string

def filter_func(c):
    if c in string.ascii_letters:
        return True
    return False

def filter_non_ascii(word):
    res = filter(filter_func, word)
    res = ''.join(list(res))
    return res

def read_content(filename, start_line):
    d = dict()
    count = 0
    for line in open(filename, encoding='UTF-8'):
        count += 1
        if count < start_line:
            continue
        for word in line.split(' '):
            word = word.strip(string.whitespace + string.punctuation)
            word = filter_non_ascii(word).lower()
            if word == '':
                continue
            if word not in d:
                d[word] = 1
            else:
                d[word] += 1
    return d


if __name__ == '__main__':
    d = read_content('Pride_and_Prejudice.txt', 165)
    l = [n for n in d.values()]
    print('Total words:', sum(l))
    l = []
    for k, v in d.items():
        l.append((v, k))
    l.sort(reverse=True)
    with open('13-1_results.txt', 'w') as fout:
        for k, v in l:
            fout.write(f'"{v}" appears {k} times\n')