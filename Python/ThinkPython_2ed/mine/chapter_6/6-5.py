def gcd(a, b):
    if b == 0:
        return a
    return gcd(b, a % b)


if __name__ == '__main__':
    print(gcd(312, 534))
    print(gcd(39, 52))
    print(gcd(75, 125))