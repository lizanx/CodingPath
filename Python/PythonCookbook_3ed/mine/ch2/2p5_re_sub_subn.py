from calendar import month_abbr
import re

text = 'Today is 11/27/2012. PyCon starts 3/13/2013.'
print(re.sub(r'(\d+)/(\d+)/(\d+)', r'\3-\1-\2', text))

pattern = re.compile(r'(\d+)/(\d+)/(\d+)')
def change_date(m):
    return f'{month_abbr[int(m.group(1))]} {m.group(2)} {m.group(3)}'
print(pattern.sub(change_date, text))

new_text, n = pattern.subn(change_date, text)
print(f'{n} matches replaced, new text: {new_text}')