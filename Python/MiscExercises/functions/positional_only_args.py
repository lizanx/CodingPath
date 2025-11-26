def add_and_print(a: int, b: int, /, msg: str) -> int:
    print(f"[add_and_print] {msg}")
    return a + b


if __name__ == "__main__":
    result = add_and_print(1, 2, "Hello")
    result = add_and_print(1, 2, msg="Hello")
    # result = add_and_print(1, b=2, "Hello") # Error: parameter 'b' is positional only
    # result = add_and_print(a=1, 2, "Hello") # Error: parameter 'a' is positional only
    # result = add_and_print(a=1, b=2, "Hello") # Error: parameters 'a' and 'b' are positional only
    print(f"1 + 2 = {result}")
