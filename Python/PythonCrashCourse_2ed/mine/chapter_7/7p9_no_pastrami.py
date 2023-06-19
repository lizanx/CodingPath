sandwich_orders = ['pastrami', 'tuna', 'egg', 'pastrami', 'hotdog', 'chicken', 'pastrami']
print("Oops! Deli has run out of pastrami!")
while 'pastrami' in sandwich_orders:
    sandwich_orders.remove('pastrami')
print(sandwich_orders)