from enum import Enum

class Color(str, Enum):
    Red = 'RED'
    Green = 'GREEN'
    Blue = 'BLUE'

class Duck:
    def __init__(self, color=Color.Green) -> None:
        self._color = color
    
    def quack(self):
        print(f"I'm a {self._color} duck!")

    @property
    def color(self):
        return self._color

    @color.setter
    def color(self, value):
        print(f'Setting color to {value}')
        self._color = value
    
    @color.deleter
    def color(self):
        print(f'Deleting color!')
        self._color = None

if __name__ == '__main__':
    duck = Duck(Color.Red)
    duck.quack()
    print(f'Color is {duck.color}')
    duck.color = Color.Blue
    print(f'Color is {duck.color}')

