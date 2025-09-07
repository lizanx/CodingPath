class Calculator:
    """A simple demo calculator."""
    def __init__(self, base_num: int) -> None:
        self.base_num = base_num
    
    def add(self, n: int) -> int:
        return n + self.base_num
    
    def minus(self, n: int) -> int:
        return n - self.base_num
    
    def multiply(self, n: int) -> int:
        return n * self.base_num
    
    def divide(self, n: int) -> int:
        return int(n / self.base_num)
