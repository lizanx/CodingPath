import re

text = 'UPPER PYTHON, lower python, Mixed Python'
print(re.sub('python', 'kotlin', text, flags=re.IGNORECASE))

def matchcase(word: str):
    def replace(m):
        old_word = m.group()
        if old_word.isupper():
            return word.upper()
        elif old_word.islower():
            return word.lower()
        elif old_word[0].isupper() and old_word[1:].islower():
            return word.capitalize()
        else:
            return word
    
    return replace
print(re.sub(pattern='python', repl=matchcase('kotlin'), string=text, flags=re.IGNORECASE))
