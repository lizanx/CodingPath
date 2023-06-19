while True:
    exp = input("Enter your calculation('q' for quit): ")
    if exp == 'q':
        break
    print("Result:", eval(exp))