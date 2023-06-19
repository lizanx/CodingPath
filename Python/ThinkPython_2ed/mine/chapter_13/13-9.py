import math

def calc_word_freq(filename, start=0):
    res = dict()
    cnt = 1
    with open(filename, encoding='UTF-8') as fin:
        for line in fin:
            if cnt < start:
                cnt += 1
                continue
            line = line.replace(',', ' ')
            line = line.replace('.', ' ')
            line = line.replace(':', ' ')
            line = line.replace('?', ' ')
            l = line.split(' ')
            for word in l:
                word = word.strip().lower()
                res[word] = res.get(word, 0) + 1
    return res

def calc_zipf(d):
    l = [(freq, word) for word, freq in d.items()]
    l.sort(reverse=True)
    for i in range(len(l)):
        print('log(f):', math.log(l[i][0]), 'log(r):', math.log(i + 1))

if __name__ == '__main__':
    calc_zipf(calc_word_freq('Pride_and_Prejudice.txt', 167))