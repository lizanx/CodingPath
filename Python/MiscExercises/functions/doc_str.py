def add_and_print(a: int, b: int, *, msg: str) -> int:
    r"""A demo function for addition and msg printing.

    Args:
        a (int): left operand for addition.
        b (int): right operand for addition.
        msg (str): extra msg to print.

    Returns:
        int: the result of addition.
    """

    print(f"[add_and_print] {msg}")
    return a + b


if __name__ == "__main__":
    print(f"Doc string:\n{add_and_print.__doc__}")
    print()
    input("Press ENTER to show help info.")
    help(add_and_print)
