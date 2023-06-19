def is_palindrome(s):
    if s == s[::-1]:
        return True
    return False


print(is_palindrome("hello"), is_palindrome('redivider'))