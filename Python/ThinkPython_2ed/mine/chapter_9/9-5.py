def is_abecedarian(s):
    if s == ''.join(sorted(s)):
        return True
    return False

print(is_abecedarian('hi'), is_abecedarian('abey'), is_abecedarian('hello'))