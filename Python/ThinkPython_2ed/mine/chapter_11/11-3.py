map = dict()
def ack(m, n):
    if m == 0:
        return n + 1
    if (m, n) in map:
        return map[(m, n)]
    if m > 0 and n == 0:
        map[(m, n)] = ack(m - 1, 1)
    elif m > 0 and n > 0:
        map[(m, n)] = ack(m - 1, ack(m, n - 1))
    return map[(m, n)]


if __name__ == '__main__':
    print(ack(3, 4))
    print(ack(10, 20))