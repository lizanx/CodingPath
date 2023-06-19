import turtle
import math

def polygon(t, length, n):
    for i in range(n):
        t.fd(length)
        t.lt(360 / n)

def circle(t, r):
    side_length = r * math.pi * 2 / 360
    t.delay = 0.01
    polygon(t, side_length, 360)

bob = turtle.Turtle()
circle(bob, 50)