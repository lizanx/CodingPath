def has_interlock(l, word):
    evens = word[::2]
    odds = word[1::2]
    if evens in l and odds in l:
        print('interlock:', evens, odds, word)

def has_interlock_general(l, word, n=3):
    flag = True
    for i in range(n):
        partial = word[i::n]
        if partial not in l:
            flag = False
            break
    if flag:
        t = [word[i::n] for i in range(n)]
        print(f'interlock-{n}:' ,' '.join(t), word)

if __name__ == '__main__':
    content = []
    with open('words.txt') as fin:
        for word in fin:
            content.append(word.strip())
    for word in content:
        has_interlock(content, word)
        has_interlock_general(content, word, 3)