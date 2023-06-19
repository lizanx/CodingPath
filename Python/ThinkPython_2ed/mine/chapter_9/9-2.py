def has_no_e(s):
    if 'e' not in s:
        return True
    return False


with open("words.txt") as fin:
    for word in fin:
        word = word.strip()
        if has_no_e(word):
            print(word)