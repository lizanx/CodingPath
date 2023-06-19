from point import Point

def calc_distance(p1, p2):
    return p1.calc_distance(p2)


if __name__ == '__main__':
    p1, p2 = Point(2, 3), Point(5, 7)
    print(calc_distance(p1, p2))