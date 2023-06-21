import re

text = 'Today is 2022/02/22, the date I might quit this job is 2022/03/27.'

print(re.findall(r'\d+/\d+/\d+', text))

date_pattern = re.compile(r'\d+/\d+/\d+')
print(date_pattern.findall(text))


date_pattern2 = re.compile(r'(\d+)/(\d+)/(\d+)')
text2 = '2022/02/22'
m = date_pattern2.match(text2)
print(f'{m.groups()}\t: {m.group(1)} - {m.group(2)} - {m.group(3)}')
print(date_pattern2.findall(text))
