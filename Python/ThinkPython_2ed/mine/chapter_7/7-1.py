import sys
import math

def square_root(a):
    x = a / 4
    while True:
        # print(x)
        y = (x + a / x) / 2
        if abs(y - x) < sys.float_info.epsilon:
            break
        x = y
    return x


if __name__ == '__main__':
    l = [1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0]
    for i in l:
        print(f'value: {i}, square_root: {square_root(i)}, math.sqrt: {math.sqrt(i)}')