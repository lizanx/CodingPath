while True:
    num_1 = input("Enter first number('q' for quit): ")
    if num_1 == 'q':
        break
    num_2 = input("Enter second number('q' for quit): ")
    if num_2 == 'q':
        break
    try:
        res = float(num_1) + float(num_2)
    except ValueError:
        print("The value you entered are not valid numbers.")
    else:
        print("The addition of your input numbers is", res)
