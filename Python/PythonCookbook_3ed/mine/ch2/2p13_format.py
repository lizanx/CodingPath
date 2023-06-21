t = 'Hello World'
print(t.ljust(20, '-'))
print(t.rjust(20, '='))
print(t.center(20, '*'))

print(format(t, '>20'))
print(format(t, '-<20'))
print(format(t, '*^20'))

print(format(3.14, '-^20.2f'))
