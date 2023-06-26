import os, re

regex = re.compile(input('Please enter the regex to search:\n'))

for file in os.listdir(os.getcwd()):
    if file.endswith('.txt'):
        with open(file) as fb:
            for line in fb:
                if regex.search(line):
                    print(line)
