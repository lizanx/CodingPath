import datetime

# 1
def get_date_in_week():
    return datetime.datetime.today().strftime('%A')


# 2
def calc_age(year):
    return datetime.datetime.year - year

def calc_time_to_next_birthday(month, day):
    now = datetime.datetime.today()
    if now.month == month and now.day == day:
        return (0, 0, 0, 0)
    elif now.month < month or (now.month == month and now.day < day):
        next_bd = datetime.datetime(now.year, month, day)
    else:
        next_bd = datetime.datetime(now.year + 1, month, day)

    delta_time = next_bd - now
    hours, seconds = divmod(delta_time.seconds, 3600)
    minutes, seconds = divmod(seconds, 60)
    return (delta_time.days, hours, minutes, seconds)


# 3
# target_date - old = 2(target_date - new)
# target_date = 2*new - old
def calc_double_birth_day(date1, date2):
    return max(date1, date2) - min(date1, date2) + max(date1, date2)




if __name__ == '__main__':
    print(get_date_in_week())
    print('remaining time until next birthday:',calc_time_to_next_birthday(11, 26))
    date1 = datetime.datetime(1973, 11, 22)
    date2 = datetime.datetime(1986, 2, 23)
    print(calc_double_birth_day(date1, date2))