from collections import OrderedDict

od = OrderedDict() # newly added items are stored by the order they're added
od['foo'] = 1
od['bar'] = 2
od['spam'] = 3
od['grok'] = 4
for key, val in od.items():
    print(f'{key}: {val}')
