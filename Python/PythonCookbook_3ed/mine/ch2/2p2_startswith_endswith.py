filenames = [ 'Makefile', 'foo.c', 'bar.py', 'spam.c', 'spam.h' ]
for filename in filenames:
    if filename.endswith(('.c', '.h')): # pass a tule for multiple possibilities
        print(f'C file: {filename}')
