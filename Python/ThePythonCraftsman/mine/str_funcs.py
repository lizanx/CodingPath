class Person:
    def __init__(self, name: str, age: int) -> None:
        self.name = name
        self.age = age
    
    def __str__(self) -> str:
        return f'{self.name}(age: {self.age})'
    
    def __repr__(self) -> str:
        return f'{self} Person(name: {self.name}, age: {self.age})'
    
    def __format__(self, __format_spec: str) -> str:
        if __format_spec == 'simple':
            return str(self)
        elif __format_spec == 'verbose':
            return repr(self)
        else:
            return 'Person'

if __name__ == '__main__':
    p = Person('Gavin', 27)
    print(f'str: {str(p)}')
    print(f'repr: {repr(p)}')
    print(f'Format simple: {p:simple}')
    print(f'Format verbose: {p:verbose}')
