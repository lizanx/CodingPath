import re

def isStrongPwd(pwd: str):
    if len(pwd) < 8:
        return False
    lowercaseRegex = re.compile(r'[a-z]')
    if not lowercaseRegex.search(pwd):
        return False
    uppercaseRegex = re.compile(r'[A-Z]')
    if not uppercaseRegex.search(pwd):
        return False
    digitRegex = re.compile(r'\d')
    if not digitRegex.search(pwd):
        return False
    return True

print(
    isStrongPwd('HelloWorld'),
    isStrongPwd('Hi90876'),
    isStrongPwd('hello8world'),
    isStrongPwd('StrongPwd111')
)