def rotate_word(s, n):
    l = [chr(ord(c) + n) for c in s]
    return ''.join(l)

def is_rotate_word(s1, s2):
    if not s1 or not s2:
        return False
    if rotate_word(s1, ord(s1[0]) - ord(s2[0])) == s2:
        return True
    return False

if __name__ == '__main__':
    d = dict()
    with open("words.txt") as fin:
        for word in fin:
            d[word.strip().lower()] = None
    for word in d:
        for i in range(1, 14):
            if rotate_word(word, i) in d:
                print(word, i, rotate_word(word, i))