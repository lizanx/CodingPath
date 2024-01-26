d = { 'Python': 'dynamic', 'C#': 'static' }

if __name__ == '__main__':
    print(next(iter(d.keys())))
    print('-----')
    print(next(i for i in [1, 2, 3, 4, 5] if i % 2 == 0))
