from inspect import signature


def add_and_print(a: int, b: int, *, msg: str = "Hello") -> int:
    print(f"[add_and_print] {msg}")
    return a + b


if __name__ == "__main__":
    sig = signature(add_and_print)
    print(sig)
    print(sig.parameters)
    print(sig.parameters["b"])
    print(sig.parameters["msg"])
    print(sig.parameters["a"].kind)
    print(sig.parameters["msg"].default)
