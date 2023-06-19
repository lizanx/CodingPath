import re

line = 'asdf fjdk; afed, fjek,asdf, foo'
print(re.split(r'[,;\s]\s*', line))
