from typing import Callable


def add_and_print(a: int, b: int, *, msg: str = "Hello") -> int:
    print(f"[add_and_print] {msg}")
    return a + b


def outer() -> Callable[[], None]:
    x = 70

    def inner() -> None:
        print(f"x = {x}")

    return inner


if __name__ == "__main__":
    print(f"== Non-closure ==")
    print(add_and_print.__closure__)
    print()
    print(f"== Closure ==")
    inner_func = outer()
    print(inner_func.__closure__)
    print(inner_func.__closure__[0].cell_contents)
