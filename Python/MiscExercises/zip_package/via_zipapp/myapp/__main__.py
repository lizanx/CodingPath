"""Entry point for myapp."""

from calculator import Calculator

if __name__ == "__main__":
    calc = Calculator()
    print(f"1 + 2 = {calc.add(1, 2)}")
    print(f"3 + 4 = {calc.add(3, 4)}")
