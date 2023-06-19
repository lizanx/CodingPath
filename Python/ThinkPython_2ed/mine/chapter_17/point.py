class Point:
    def __init__(self, x=0, y=0):
         self.x = x
         self.y = y

    def __str__(self):
        return f'({self.x}, {self.y})'
    
    def __add__(self, other):
        if isinstance(other, Point):
            return Point(self.x + other.x, self.y + other.y)
        elif isinstance(other, tuple):
            return Point(self.x + other[0], self.y + other[1])
        print("Error: unknown add type")
        return None


if __name__ == '__main__':
    p1 = Point(1, 2)
    p2 = p1 + Point(2, 3)
    p3 = p1 + (4, 5)
    print(p1, p2, p3)