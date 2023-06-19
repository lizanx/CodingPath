sandwich_orders = ['tuna', 'egg', 'hotdog', 'chicken']
finished_sandwiches = []
while sandwich_orders:
    sandwich = sandwich_orders.pop()
    print(f"I made your {sandwich} sandwich")
    finished_sandwiches.append(sandwich)
print("\nAll the sandwiches made:")
for sandwich in finished_sandwiches:
    print(f"\t{sandwich}")