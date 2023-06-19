with open("words.txt") as fin:
    for word in fin:
        word = word.strip()
        if len(word) > 20:
            print(word)