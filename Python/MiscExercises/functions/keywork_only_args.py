def add_and_print(a: int, b: int, *, msg: str) -> int:
    print(f"[add_and_print] {msg}")
    return a + b


if __name__ == "__main__":
    # result = add_and_print(1, 2, "Hello") # Error: parameter 'msg' is keyword only
    result = add_and_print(1, 2, msg="Hello")
    result = add_and_print(a=1, b=2, msg="Hello")
    print(f"1 + 2 = {result}")
