from functools import partial

if __name__ == "__main__":
    len_sort = partial(sorted, key=len)
    fruits = ["orange", "banana", "apple"]
    sorted_alphabetically = sorted(fruits)
    print(sorted_alphabetically)
    sorted_by_len = len_sort(fruits)
    print(sorted_by_len)
