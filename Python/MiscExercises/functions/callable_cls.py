from typing import Callable


class Adder:
    def __init__(self, operand: int) -> None:
        self._operand = operand

    def __call__(self, n: int) -> int:
        return self._operand + n


def create_adder(n: int) -> Callable[[int], int]:
    return Adder(n)


if __name__ == "__main__":
    print(type(int), callable(int))
    print(type(str), callable(str))
    print(type(print), callable(print))

    add_5 = create_adder(5)
    print(type(add_5), callable(add_5))
    print(add_5(10))
