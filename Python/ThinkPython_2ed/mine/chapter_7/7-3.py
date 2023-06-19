import math
import sys

def calc(k):
    return math.factorial(4 * k) * (1103 + 26390 * k) / ((math.factorial(k))**4 * (396**(4 * k)))


i = 1
while True:
    calc_res = calc(i)
    res = calc_res * 2 * math.sqrt(2) / 9801
    if res < 1e-15:
        print("i:", i,", approxiamate pi:", res)
        break
    i += 1