import turtle

def square(t, length):
    for i in range(4):
        t.fd(length)
        t.lt(90)

bob = turtle.Turtle()
square(bob, 50)
square(bob, 100)