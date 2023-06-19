import time

def get_content(file_name):
    l = []
    with open(file_name) as fin:
        for word in fin:
            l.append(word)
    return l

def get_content_alter(file_name):
    l = []
    with open(file_name) as fin:
        for word in fin:
            l = l + [word]
    return l

if __name__ == '__main__':
    t1 = time.time()
    l1 = get_content("words.txt")
    t2 = time.time()
    l2 = get_content("words.txt")
    t3 = time.time()
    print(f'method of using "append" consumes {t2 - t1}s, using "+" consumes {t3 - t2}s')