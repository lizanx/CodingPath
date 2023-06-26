import re

def myStrip(s: str, sym: str = ''):
    prefixRegex = re.compile('^' + sym if sym else r'\s' + '+')
    postfixRegex = re.compile(sym if sym else r'\s' + '+' + '$')
    return prefixRegex.sub('', postfixRegex.sub('', s))

print(
    myStrip('  Hi'),
    myStrip('Hello  \t\t'),
    myStrip('world'),
    myStrip('\tnice day!  '),
    sep='##\n',
    end='##\n'
)