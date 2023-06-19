def contain_triple_double(s):
    i = 0
    while i < len(s):
        if i + 5 < len(s):
            if s[i] == s[i + 1] and s[i + 2] == s[i + 3] and s[i + 4] == s[i + 5]:
                return True
            else:
                i += 1
        else:
            return False

with open('words.txt') as fin:
    for word in fin:
        word = word.strip()
        if contain_triple_double(word):
            print(word)