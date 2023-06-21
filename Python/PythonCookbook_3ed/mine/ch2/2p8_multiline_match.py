import re

comment1 = '/* this is a single line comment in C */'
comment2 = '''/* This is a multi-line comment in C
    * line2
    * line3
    */'''

pattern1 = re.compile(r'/\*(.*?)\*/') # by default, '.' cannot match '\n'
print(f'pattern1:\t{pattern1.findall(comment1)}')
print(f'pattern1:\t{pattern1.findall(comment2)}')

pattern2 = re.compile(r'/\*((?:.|\n)*?)\*/')
print(f'pattern2:\t\t{pattern2.findall(comment1)}')
print(f'pattern2:\t\t{pattern2.findall(comment2)}')

pattern3 = re.compile(r'/\*(.*?)\*/', flags=re.DOTALL) # this flag makes '.' matches '\n'
print(f'pattern3:\t\t{pattern3.findall(comment1)}')
print(f'pattern3:\t\t{pattern3.findall(comment2)}')
