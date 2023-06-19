import random

def has_same_birthday(l):
    for d in l:
        if l.count(d) > 1:
            return True
    return False

def generate_birthdays(n):
    l = []
    for i in range(n):
        month = random.randint(1, 12)
        day = 0
        if month == 2:
            year = random.randint(1930, 2021)
            if year % 4 == 0:
                day = random.randint(1, 29)
            else:
                day = random.randint(1, 28)
        elif month == 4 or month == 6 or month == 9 or month == 11:
            day = random.randint(1, 30)
        else:
            day = random.randint(1, 31)
        l.append(str(month) + '-' + str(day))
    return l

if __name__ == '__main__':
    cnt = 0
    for i in range(100000):
        l = generate_birthdays(23)
        if has_same_birthday(l):
            cnt += 1
    print('With 100000 simulations, probablity is', cnt / 100000)