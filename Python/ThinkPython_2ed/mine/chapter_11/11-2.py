def invert_dict(d):
    new_d = dict()
    for k, v in d.items():
        new_d.setdefault(v, []).append(k)
    return new_d

if __name__ == '__main__':
    d = {'a':1, 'b':2, 'c':3, 'x':3, 'y':2, 'z':4}
    print(invert_dict(d))