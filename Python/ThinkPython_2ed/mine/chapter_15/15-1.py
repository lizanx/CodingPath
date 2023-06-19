from point import Point
from rectangle import Rectangle
from circle import Circle

def point_in_circle(p, c):
    return p.calc_distance(c.center) <= c.radius

def rect_in_circle(r, c):
    return point_in_circle(r.corner, c) and point_in_circle(Point(r.corner.x + r.width, r.corner.y), c) \
        and point_in_circle(Point(r.corner.x, r.corner.y + r.height), c) \
            and point_in_circle(Point(r.corner.x + r.width, r.corner.y + r.height), c)

if __name__ == '__main__':
    circle = Circle(Point(150, 100), 75)
    p = Point(200, 110)
    r = Rectangle(Point(150, 100), 30, 30)
    print(point_in_circle(p, circle), rect_in_circle(r, circle))