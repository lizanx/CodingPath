import turtle

def square(t):
    for i in range(4):
        t.fd(300)
        t.lt(90)

bob = turtle.Turtle()
square(bob)