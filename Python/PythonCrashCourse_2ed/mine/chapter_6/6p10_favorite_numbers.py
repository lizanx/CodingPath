fav_nums = {
    'gavin': [17, 19],
    'Diana': [13],
    'Lee': [6, 24],
    'Qcom': [625, 660, 855, 888],
    'Dan': [4, 14, 69],
}

for person, nums in fav_nums.items():
    print(f"The favorite numbers of {person} are:")
    for num in nums:
        print(num)
    print()