def is_triangle(a, b, c):
    if a >= b + c or b >= a + c or c >= a + b or a <= 0 or b <= 0 or c <= 0:
        return False
    return True


if __name__ == '__main__':
    print("Please enter three integers('q' for quit):")
    while True:
        data = input("Enter your numbers: ")
        if 'q' in data or 'Q' in data:
            break
        nums = data.split()
        if len(nums) != 3:
            print("3 integers, please retry!")
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
        if is_triangle(nums[0], nums[1], nums[2]):
            print("Can form a triangle!")
        else:
            print('Can not form a triangle!')
    print('exit')