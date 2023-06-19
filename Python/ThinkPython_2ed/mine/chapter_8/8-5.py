def rotate_word(s, n):
    l = [chr(ord(c) + n) for c in s]
    return ''.join(l)


print("Hello ->", rotate_word('Hello', 3), "\nWorld ->", rotate_word('World', 2))