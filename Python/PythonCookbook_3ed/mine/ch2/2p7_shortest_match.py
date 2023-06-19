import re

text = '"Python" is a dynamic-type language, while "Kotlin" is a static-type language.'

str_pat = re.compile(r'\"(.*)\"')
print(str_pat.findall(text))

str_pat_2 = re.compile(r'\"(.*?)\"') # an ending '?' denotes non-greedy mode
print(str_pat_2.findall(text))
