import math

class Point:
    """Denotes a point on a 2-D surface."""
    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y
    
    def calc_distance(self, p):
        return math.sqrt((self.x - p.x)**2 + (self.y - p.y)**2)