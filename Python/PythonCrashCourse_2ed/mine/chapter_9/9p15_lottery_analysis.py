from random import choice

t = (0,1,2,3,4,5,6,7,8,9,'a','b','c','d','e')
my_tick = (1,7,'c','e')
cnt = 0
while True:
    res = []
    while len(res) < 4:
        res.append(choice(t))
    res_check = res[:]
    cnt += 1
    flag = False
    for e in my_tick:
        if e in res_check:
            res_check.remove(e)
        else:
            break
    if res_check == []:
        flag = True
    if flag:
        print("Win! res =", res, "\tmy_ticket =", my_tick, "\t cnt =", cnt)
        break
