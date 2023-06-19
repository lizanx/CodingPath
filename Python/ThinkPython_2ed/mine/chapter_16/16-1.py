import my_time

def mul_time(t, multiple):
    return my_time.int_to_time(int(my_time.time_to_int(t) * multiple))

def calc_time_per_mile(t, distance):
    return mul_time(t, 1 / distance)

if __name__ == '__main__':
    t = my_time.Time(1, 2, 3)
    my_time.print_time(mul_time(t, 3))
    my_time.print_time(calc_time_per_mile(t, 2))