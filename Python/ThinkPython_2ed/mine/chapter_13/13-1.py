import string

def read_content(filename):
    res = []
    for line in open(filename):
        l = line.split(' ')
        for word in l:
            res.append(word.strip(string.whitespace + string.punctuation))
    return res


if __name__ == '__main__':
    content = read_content('test.txt')
    print(content)