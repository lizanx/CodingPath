# Use named slice instead of hard-coded index to retrieve data.
data = 'Price is 45.3, amount is 20. Please calculate the total cost.'
PRICE = slice(9, 13)
AMOUNT = slice(25, 27)
total_cost = float(data[PRICE]) * int(data[AMOUNT])
print(f'Total cost is {total_cost}')

# slice.indices(size) restricts the max index to avoid IndexError.
data = 'Hello,Python!'
s = slice(0, 50, 3)
print(s)
print(s.indices(len(data))) # return a tuple: (start, stop, step)
for i in range(*s.indices(len(data))):
    print(data[i])
