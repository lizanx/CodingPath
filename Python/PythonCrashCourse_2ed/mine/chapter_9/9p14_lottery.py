from random import choice

t = (0,1,2,3,4,5,6,7,8,9,'a','b','c','d','e')
res = []
res.append(choice(t))
res.append(choice(t))
res.append(choice(t))
res.append(choice(t))
print("Any ticket that matches the contents below wins the prize:\n", res)