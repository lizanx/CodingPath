class Range3:
    def __init__(self, start: int, end: int) -> None:
        self.start = start
        self.end = end
    
    def __iter__(self):
        return Range3Iter(self)
    
class Range3Iter:
    def __init__(self, range: Range3) -> None:
        self.range = range
        self.current = range.start
    
    def __iter__(self):
        return self
    
    def __next__(self):
        while self.current < self.range.end:
            if self.current % 3 == 0:
                ret = self.current
                self.current += 1
                return ret
            self.current += 1
        raise StopIteration

if __name__ == '__main__':
    r1 = Range3(1, 10)
    r2 = Range3(11, 50)
    r3 = Range3(80, 100)
    for n in r1:
        print(f'{n} ', end='')
    print()
    for n in r2:
        print(f'{n} ', end='')
    print()
    for n in r3:
        print(f'{n} ', end='')
    print()
