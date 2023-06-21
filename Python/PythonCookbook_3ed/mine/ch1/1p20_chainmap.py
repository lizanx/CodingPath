from collections import ChainMap

a = {'x': 1, 'z': 3, 'p': 5}
b = {'y': 2, 'z': 4, 'p': 6}
c = ChainMap(a, b)
print(c)
# for duplacated keys, only the first map is considered
print(f'c: len={len(c)} c[x]={c["x"]} c[y]={c["y"]} c[z]={c["z"]} c[p]={c["p"]}')

a['x'] = 11
b['y'] = 22
b['p'] = 66
# ChainMap doesn't create new map, thus changes to underlined a/b affects c
print(f'c: len={len(c)} c[x]={c["x"]} c[y]={c["y"]} c[z]={c["z"]} c[p]={c["p"]}')

c['p'] = 55
c['z'] = 33
# changes via c for duplicated keys affect the first underlined map only
print(f'a: {a}\nb: {b}')

c['y'] = 222
# event if non-first underlined maps contains a key that first underlined map doesn't
# assignment via c will add a new key:value pair in the first underlined map
print(f'a: {a}\nb: {b}')


# new_child --> ChainMap({}, c)
c2 = c.new_child()
c2['x'] = 111
print(f'c2:\t{c2}')

# parents -->  ChainMap(c2[1:])
c3 = c2.parents
print(f'c3:\t{c3}')
