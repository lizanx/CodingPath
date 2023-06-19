def signature(s):
    return ''.join(sorted(s))

def all_anagrams(filename):
    d = dict()
    for word in open(filename):
        word = word.strip().lower()
        if signature(word) not in d:
            d[signature(word)] = [word]
        else:
            d[signature(word)].append(word)
    return d



if __name__ == '__main__':
    d = all_anagrams('words.txt')
    # for k, v in d.items():
    #     print(k, v)
    l = []
    for val in d.values():
        l.append((len(val), val))
    l.sort(reverse=True)
    with open('12-2_results.txt', 'a') as fout:
        for e in l:
            fout.write(str(e) + '\n')