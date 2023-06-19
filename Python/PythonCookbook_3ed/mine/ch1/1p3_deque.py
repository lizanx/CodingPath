from collections import deque

d = deque(maxlen=3)
d.append(1)
d.append(2)
d.append(3)
print(d)
d.append(4)
print(d)