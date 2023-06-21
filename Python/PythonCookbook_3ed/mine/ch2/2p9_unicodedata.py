import unicodedata

s1 = 'Spicy Jalape\u00f1o'
s2 = 'Spicy Jalapen\u0303o'
print(f's1: {s1}\ns2: {s2}\ns1==s2: {s1 == s2}')

normalized_s1 = unicodedata.normalize('NFC', s1)
normalized_s2 = unicodedata.normalize('NFC', s2)
print(f'normalized_s1: {normalized_s1}')
print(f'normalized_s2: {normalized_s2}')
print(f'normalized_s1 == normalized_s2: {normalized_s1 == normalized_s2}')
