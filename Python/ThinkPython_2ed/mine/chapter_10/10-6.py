def is_anagram(s1, s2):
    res = list(s2)
    for c in s1:
        if c not in s2:
            return False
        res.remove(c)
    if len(res) == 0:
        return True
    return False

print(is_anagram('hello', 'eolhl'), is_anagram('sunday', 'sunny'))