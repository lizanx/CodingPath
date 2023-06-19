import turtle
import math

def move_to_next_pos(t, size):
    t.pu()
    t.fd(size / 2)
    t.pd()

def draw_h(t, size):
    t.lt(90)
    t.fd(size)
    t.rt(180)
    t.fd(size / 2)
    t.lt(90)
    t.fd(size * 2 / 3)
    t.lt(90)
    t.fd(size / 2)
    t.rt(180)
    t.fd(size)
    t.lt(90)

def draw_e(t, size):
    t.fd(size / 2)
    t.rt(180)
    t.fd(size / 2)
    t.rt(90)
    t.fd(size / 2)
    t.rt(90)
    t.fd(size / 2)
    t.rt(180)
    t.fd(size / 2)
    t.rt(90)
    t.fd(size / 2)
    t.rt(90)
    t.fd(size / 2)
    t.pu()
    t.fd(size / 2)
    t.rt(90)
    t.fd(size)
    t.lt(90)
    t.pd()

def draw_l(t, size):
    t.lt(90)
    t.fd(size)
    t.rt(180)
    t.fd(size)
    t.lt(90)
    t.fd(size / 2)
    t.pu()
    t.fd(size / 2)

def polyline(t, n, length, angle):
    t.delay = 0.01
    for i in range(n):
        t.fd(length)
        t.lt(angle)

def polygon(t, length, n):
    polyline(t, n, length, 360 / n)

def arc(t, r, angle):
    arc_length = 2 * math.pi * r * abs(angle) / 360
    n = int(arc_length / 4) + 3
    step_length = arc_length / n
    step_angle = float(angle) / n

    # making a slight left turn before starting reduces
    # the error caused by the linear approximation of the arc
    t.lt(step_angle/2)
    polyline(t, n, step_length, step_angle)
    t.rt(step_angle/2)

def circle(t, r):
    arc(t, r, 360)

def draw_o(t, size):
    t.pu()
    t.fd(size / 2)
    t.pd()
    circle(t, size / 2)


if __name__ == '__main__':
    t = turtle.Turtle()
    t.pu()
    t.lt(180)
    t.fd(400)
    t.rt(180)
    t.pd()
    # HELLO
    size = 100
    draw_h(t, size)
    move_to_next_pos(t, size)
    draw_e(t, size)
    move_to_next_pos(t, size)
    draw_l(t, size)
    move_to_next_pos(t, size)
    draw_l(t, size)
    move_to_next_pos(t, size)
    draw_o(t, size)
    turtle.mainloop()