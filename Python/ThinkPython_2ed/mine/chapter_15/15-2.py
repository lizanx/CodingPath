import turtle

from point import Point
from rectangle import Rectangle
from circle import Circle

def draw_rect(r, t):
    t.penup()
    t.setpos(r.corner.x, r.corner.y)
    t.setheading(0)
    t.pendown()
    t.forward(r.width)
    t.left(90)
    t.forward(r.height)
    t.left(90)
    t.forward(r.width)
    t.left(90)
    t.forward(r.height)

def draw_circle(c, t):
    t.penup()
    t.setheading(90)
    t.setpos(c.center.x + c.radius, c.center.y)
    t.pendown()
    t.circle(c.radius)

if __name__ == '__main__':
    r = Rectangle(Point(30, 50), 50, 30)
    c = Circle(Point(200, 200), 100)
    t = turtle.Turtle()
    draw_rect(r, t)
    draw_circle(c, t)
    turtle.mainloop()