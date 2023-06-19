import turtle

def draw_koch(t, size):
    if size < 10:
        t.fd(size)
        return
    draw_koch(t, size / 3)
    t.lt(60)
    draw_koch(t, size / 3)
    t.rt(120)
    draw_koch(t, size / 3)
    t.lt(60)
    draw_koch(t, size / 3)

def draw_snowflake(t, size):
    for n in range(6):
        draw_koch(t, size)
        t.rt(360 / 6)

if __name__ == '__main__':
    t = turtle.Turtle()
    t.delay = 0.01
    # draw_koch(t, 50)
    draw_snowflake(t, 50)
    turtle.mainloop()