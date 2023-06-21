import re

t1 = '   Hello   World  \n'
print(t1.strip())
print(t1.lstrip())
t2 = '-----Hello World====='
print(t2.lstrip('-'))
print(t2.rstrip('='))

print(re.sub(r'\s+', ' ', t1.strip())) # replace multiple spaces with only one
