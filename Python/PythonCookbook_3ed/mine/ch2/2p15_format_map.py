s = '{name} is {age} years old.'
print(s.format(name='Gavin', age=25))
# print(s.format(age=25)) # KeyError: name is missing

name = 'Gavin'
# age = 25 # if you don't define age variable, call in next line will raise KeyError
# print(s.format_map(vars()))

class Person:
    def __init__(self, name: str, age: int) -> None:
        self.name = name
        self.age = age
gavin = Person('Gavin', 25)
print(s.format_map(vars(gavin)))


# Subclass of dict with a __missing__ function can avoid the KeyError.
class SafeSub(dict):
    def __missing__(self, key) -> str:
        return '{' + str(key) + '}'
print(s.format_map(SafeSub(vars())))
