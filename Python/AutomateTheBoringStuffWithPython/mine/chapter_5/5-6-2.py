def addToInventory(inventory: dict, addedItems: list):
    for item in addedItems:
        inventory.setdefault(item, 0)
        inventory[item] += 1
    return inventory
