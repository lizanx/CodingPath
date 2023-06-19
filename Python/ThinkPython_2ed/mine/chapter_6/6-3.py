def first(word):
    return word[0]

def last(word):
    return word[-1]

def middle(word):
    if len(word) < 2:
        return word
    return word[1:-1]


# print(middle('aa'))
# print(middle('ab'))
# print(middle('a'))
# print(middle('  '))

def is_palindrome(s):
    if len(s) == 1:
        return True
    if len(s) == 2:
        return first(s) == last(s)
    if first(s) != last(s):
        return False
    return is_palindrome(middle(s))


if __name__ == '__main__':
    print(is_palindrome("noon"))
    print(is_palindrome("redivider"))
    print(is_palindrome('hello'))