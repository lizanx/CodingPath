def recurse(n, s):
    if n == 0:
        print(s)
    else:
        recurse(n-1, n+s)

recurse(3, 0) # 6

# never ends
# recurse(-1 ,0)