key_words = {
    'list': 'A data structure to store data by index',
    'dictionary': 'A data structure to store key-value pairs',
    'if': 'A conditional judgement',
    'if-elif-else': 'Multiple conditional scenes',
    'for': 'A loop method',
}

for key in key_words:
    print(f"Keyword '{key}' in python means:\n{key_words[key]}\n")

key_words['title'] = 'A method to capitalize the first letter of each word and leave the remaining lower-case'
key_words['lower'] = 'A method to convert all letters to lower-case'
key_words['upper'] = 'A method to convert all letters to upper-case'
key_words['reverse'] = 'A method to reverse the order of elements stored in a list'
key_words['sort'] = 'A method to sort all elements in a list with alphabetic order'
for key, value in key_words.items():
    print(f"Keyword '{key}' in python means:\n{value}\n")
