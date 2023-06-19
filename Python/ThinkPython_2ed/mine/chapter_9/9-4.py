def uses_all(word, s):
    for c in word:
        if c not in s:
            return False
    return True


print(uses_all('adminitration', 'adimntro'))