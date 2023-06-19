import turtle
import math

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


def petal(t, r, angle):
    arc(t, r, angle)
    t.lt(180 - angle)
    arc(t, r, angle)
    t.lt(180 - angle)

def flower(t, radius, angle, petals):
    for i in range(petals):
        petal(t, radius, angle)
        t.lt(360 / petals)

bob = turtle.Turtle()
flower(bob, 200, 90, 8)