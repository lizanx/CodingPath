a = {
    'x' : 1,
    'y' : 2,
    'z' : 3
}
b = {
    'w' : 10,
    'x' : 11,
    'y' : 2
}

# keys in both a and b
print(a.keys() & b.keys())
# items in both a and b
print(a.items() & b.items())
# values in both a and b: return value of values() doesn't support set operations directly
print(set(a.values()) & set(b.values()))
# keys in a while not in b
print(a.keys() - b.keys())