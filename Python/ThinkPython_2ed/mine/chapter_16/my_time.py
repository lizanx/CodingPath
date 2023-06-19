import copy

class Time:
    def __init__(self, h=0, m=0, s=0):
        self.hour = h
        self.minute = m
        self.second = s

def print_time(t):
    print('%.2d:%.2d:%.2d' % (t.hour, t.minute, t.second))

def is_after(t1, t2):
    return t1.hour > t2.hour or (t1.hour == t2.hour and t1,minute > t2.minute) or \
        (t1.hour == t2.hour and t1.minute == t2.minute and t1.second > t2.second)

def time_to_int(t):
    return t.hour * 3600 + t.minute * 60 + t.second

def int_to_time(secs):
    t = Time()
    t.minute, t.second = divmod(secs, 60)
    t.hour, t.minute = divmod(t.minute, 60)
    return t

def add_time(t1, t2):
    return int_to_time(time_to_int(t1) + time_to_int(t2))

def increment(t, secs):
    # t.hour += secs // 3600
    # t.minute += (secs % 3600) // 60
    # t.second += secs % 60

    # new method: use time/int conversion
    return int_to_time(time_to_int(t) + secs)

def increment_func_style(t, secs):
    res = copy.copy(t)
    res.hour += secs // 3600
    res.minute += (secs % 3600) // 60
    res.second += secs % 60
    return res

def validate_time(t):
    if t.hour < 0 or t.minute < 0 or t.second < 0 or t.minute >= 60 or t.second >= 60:
        return False
    return True


if __name__ == '__main__':
    t1, t2 = Time(1, 2, 3), Time(2, 3, 4)
    print_time(t1)
    print_time(t2)
    print(is_after(t2, t1))
    # increment(t1, 6305)
    t1 = increment(t1, 6305)

    print_time(t1)
    print_time(increment_func_style(t2, 6305))

    print(validate_time(t1), validate_time(t2))