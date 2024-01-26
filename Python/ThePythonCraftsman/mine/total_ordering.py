from functools import total_ordering

@total_ordering
class Square:
    def __init__(self, length: int) -> None:
        self.length = length
    def __eq__(self, __value: object) -> bool:
        if isinstance(__value, self.__class__):
            return self.length == __value.length
        return False
    def __lt__(self, other) -> bool:
        if isinstance(other, self.__class__):
            return self.length < other.length
        return NotImplemented


if __name__ == '__main__':
    a = Square(3)
    b = Square(4)
    c = Square(5)
    d = Square(4)
    print(a == b, b != c, c > d, d == b, a <= d)
