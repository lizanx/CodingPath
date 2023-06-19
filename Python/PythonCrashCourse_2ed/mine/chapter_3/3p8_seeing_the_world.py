places = ["Silicon Valley", "Norway", "Finland", "Italy", "Australia"]
print("original:", places)
print("sorted:", sorted(places))
print("original:", places)
print("reversely sorted:", sorted(places, reverse=True))
print("original:", places)

places.reverse()
print("reversed:", places)
places.reverse()
print("original:", places)

places.sort()
print("sort:", places)
places.sort(reverse=True)
print("reversely sort:", places)