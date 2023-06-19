import turtle
import math

def arc(t, r, angle):
    side_length = r * math.pi * 2 / 360
    t.delay = 0.01
    for i in range(angle):
        t.fd(side_length)
        t.lt(1)

bob = turtle.Turtle()
arc(bob, 50, 90)
bob2 = turtle.Turtle()
arc(bob2, 100, 360)