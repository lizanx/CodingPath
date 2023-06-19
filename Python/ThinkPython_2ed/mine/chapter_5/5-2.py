def check_fermat(a, b, c, n):
    if n < 2 or a <= 0 or b <= 0 or c <= 0:
        print("Invalid arguements!")
        return
    if a ** n + b ** n == c ** n:
        print("Fermat is wrong!")
    else:
        print("Fermat is correct.")


if __name__ == '__main__':
    print("Please enter four integers to check Fermat's law('q' for quit):")
    while True:
        data = input("Enter your numbers: ")
        if 'q' in data or 'Q' in data:
            break
        nums = data.split()
        if len(nums) != 4:
            print("4 integers, please retry!")
            continue
        input_error = False
        for n in nums:
            try:
                num = int(n)
            except ValueError:
                input_error = True
                print("Invalid input:", n)
                break
            else:
                pass
        if input_error:
            continue
        nums = [int(n) for n in nums]
        check_fermat(nums[0], nums[1], nums[2], nums[3])
    print('exit')