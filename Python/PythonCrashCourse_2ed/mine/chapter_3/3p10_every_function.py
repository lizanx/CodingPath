items = ["Shenzhen", "Ferrari", "England", "French"]
print("length is", len(items))
items.append("Yellow River")
items.insert(0, "Anhui Province")
del items[1]
items.remove("England")
print(items)
items.sort()
items.reverse()
print(items)