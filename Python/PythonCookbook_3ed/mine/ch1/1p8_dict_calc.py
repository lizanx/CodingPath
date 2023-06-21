prices = {
    'ACME': 45.23,
    'AAPL': 612.78,
    'IBM': 205.55,
    'HPQ': 37.20,
    'FB': 10.75
}

max_price = max(zip(prices.values(), prices.keys()))
min_price = min(zip(prices.values(), prices.keys()))
print(f'max_price: {max_price}, min_price: {min_price}')

max_company = max(prices, key=lambda k: prices[k])
min_company = min(prices, key=lambda k: prices[k])
print(f'MAX\t{max_company}: {prices[max_company]}\nMIN\t{min_company}: {prices[min_company]}')
