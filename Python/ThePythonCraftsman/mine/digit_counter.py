from functools import partial

def read_file_digits(fp, block_size = 1024 * 8):
    _read_chunk = partial(fp.read, block_size)
    for chunk in iter(_read_chunk, ''):
        for char in chunk:
            if char.isdigit():
                yield char

def count_digits(file_name: str):
    cnt = 0
    with open(file_name, encoding='utf-8') as fp:
        for _ in read_file_digits(fp):
            cnt += 1
    return cnt

def count_even(file_name: str):
    cnt = 0
    with open(file_name, encoding='utf-8') as fp:
        for num in read_file_digits(fp):
            if int(num) % 2 == 0:
                cnt += 1
    return cnt

if __name__ == '__main__':
    print(count_digits('Frankenstein.txt'))
    print(count_even('Frankenstein.txt'))
