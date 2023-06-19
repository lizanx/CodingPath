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
        line = line.replace(',', ' ')
        line = line.replace('.', ' ')
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

def subtract_set(s1, s2):
    s = set()
    for e in s1:
        if e not in s2:
            s.add(e)
    return s

if __name__ == '__main__':
    d = read_content('Pride_and_Prejudice.txt', 165)
    l = read_word_list('words.txt')
    book_words_set = set(d.keys())
    dict_words_set = set(l)
    print(subtract_set(book_words_set, dict_words_set))