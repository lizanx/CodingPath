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

def read_word_list(filename):
    l = []
    for word in open(filename):
        l.append(word.strip().lower())
    return l

if __name__ == '__main__':
    d = read_content('Pride_and_Prejudice.txt', 165)
    l = read_word_list('words.txt')
    for word in d:
        if word not in l:
            print(word)