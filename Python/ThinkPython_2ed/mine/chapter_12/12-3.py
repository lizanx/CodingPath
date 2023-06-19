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

def is_convertible(s1, s2):
    if len(s1) != len(s2):
        return False
    cnt = 0
    diff = 0
    for i in range(len(s1)):
        if s1[i] != s2[i]:
            cnt += 1
            diff += ord(s1[i]) - ord(s2[i])
    if cnt == 2 and diff == 0:
        return True
    return False


if __name__ == '__main__':
    d = all_anagrams('words.txt')
    for l in d.values():
        if len(l) < 2:
            continue
        for word in l:
            for word2 in l[1:]:
                if is_convertible(word, word2):
                    print(word, word2)