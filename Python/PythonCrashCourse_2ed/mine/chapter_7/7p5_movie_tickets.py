while True:
    age = int(input("Please enter your age to calculate the ticket price: "))
    if age < 3:
        ticket_price = 0
    elif age <= 12:
        ticket_price = 10
    else:
        ticket_price = 15
    print(f"The price of the ticket for you is ${ticket_price}")