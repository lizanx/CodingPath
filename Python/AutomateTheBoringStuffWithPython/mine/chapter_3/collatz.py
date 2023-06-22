def collatz(num: int):
    result = num // 2 if num % 2 == 0 else 3 * num + 1
    print(result)
    return result

if __name__ == '__main__':
    collatz_result = 0
    while True:
        try:
            collatz_result = int(input('Please enter an integer: '))
            break
        except ValueError:
            print('You must enter an integer!')
    while collatz_result != 1:
        collatz_result = collatz(collatz_result)
