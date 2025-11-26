def gen_fibonacci(n: int):
    if n <= 0:
        raise RuntimeError(f"Invalid n {n}")
    a = 1
    b = 1
    yield a
    n -= 1
    if n <= 0:
        return
    yield b
    n -= 1
    if n <= 0:
        return
    while True and n > 0:
        tmp = b
        b = a + b
        a = tmp
        yield b
        n -= 1


if __name__ == "__main__":
    for i in gen_fibonacci(10):
        print(i)
