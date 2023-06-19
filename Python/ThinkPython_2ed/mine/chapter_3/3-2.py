# 1
def do_twice(f):
    f()
    f()

def print_spam():
    print('spam')

do_twice(print_spam)

# 2
def do_twice_with_para(func, para):
    func(para)
    func(para)

def print_twice(s):
    print(s)
    print(s)

do_twice_with_para(print_twice, "spam_2")

# 3
def do_four(func, para):
    do_twice_with_para(func, para)
    do_twice_with_para(func, para)

do_four(print, "spam_4")