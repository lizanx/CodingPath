def is_palindrome(s):
    if s == s[::-1]:
        return True
    return False


for i in range(999999):
    if is_palindrome(str(i % 10000)):
        i += 1
        if is_palindrome(str(i % 100000)):
            i += 1
            if is_palindrome(str(int(i / 10) % 10000)):
                i += 1
                if is_palindrome(str(i)):
                    print(i)