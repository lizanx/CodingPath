import time

if __name__ == '__main__':
    l = []
    d = dict()
    with open("words.txt") as fin:
        for word in fin:
            word = word.strip()
            l.append(word)
            d[word] = 1
    start_time = time.time()
    print('Is "reclasped" contained? ', 'reclasped' in l)
    elapsed_time = time.time() - start_time
    start_time = time.time()
    print('Is "reclasped" contained? ', 'reclasped' in d)
    elapsed_time_2 = time.time() - start_time
    print('time consumed by list search:', elapsed_time, 'time consumed by dict search:', elapsed_time_2)