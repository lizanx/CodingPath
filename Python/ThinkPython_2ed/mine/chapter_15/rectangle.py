from point import Point

class Rectangle:
    def __init__(self, p=Point(0, 0), width=0, height=0):
        self.corner = p
        self.width = width
        self.height = height

