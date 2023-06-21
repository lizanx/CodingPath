import re

pat = re.compile('stra\u00dfe', re.IGNORECASE)
s = 'straße'
print(pat.match(s)) # Match.
print(pat.match(s.upper())) # Doesn't match.
print(s.upper()) # Case folds.
