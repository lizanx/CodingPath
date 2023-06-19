prices = {
    'ACME': 45.23,
    'AAPL': 612.78,
    'IBM': 205.55,
    'HPQ': 37.20,
    'FB': 10.75
}

tech_names = {'AAPL', 'IBM', 'HPQ', 'MSFT'}

tech_prices = { key:value for key, value in prices.items() if key in tech_names}
tech_prices_2 = dict((key, value) for key, value in prices.items() if key in tech_names)
print(f'tech comany prices:\n{tech_prices}\n\n{tech_prices_2}')