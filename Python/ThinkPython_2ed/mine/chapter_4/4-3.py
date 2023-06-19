import turtle
import math
import time

def polyline(t, n, length, angle):
    t.delay = 0.01
    for i in range(n):
        t.fd(length)
        t.lt(angle)

def polygon(t, length, n):
    polyline(t, n, length, 360 / n)

def skeleton(t, length, n):
    for i in range(n):
        t.fd(length)
        t.lt(180)
        t.fd(length)
        t.lt(180)
        t.lt(360 / n)

def skeleton_polygon(t, length, n):
    skeleton_length = length / (2 * math.sin(math.pi / n))
    skeleton(t, skeleton_length, n)
    t.fd(skeleton_length)
    t.lt(90 + 180 / n)
    polygon(t, length, n)


bob = turtle.Turtle()
# skeleton_polygon(bob, 50, 8)
skeleton_polygon(bob, 50, 6)
time.sleep(3)