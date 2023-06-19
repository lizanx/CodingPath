def are_reversed(i, j):
    return str(i).zfill(2) == str(j).zfill(2)[::-1]

def num_instances(diff, flag=False):
    daughter = 0
    cnt = 0
    while True:
        mother = daughter + diff
        if are_reversed(daughter, mother) or are_reversed(daughter, mother + 1):
            cnt += 1
            if flag:
                print("daughter:", daughter, "mother:", mother)
        if mother > 120:
            break
        daughter += 1
    return cnt

def check_diffs():
    diff = 10
    while diff < 70:
        n = num_instances(diff)
        if n == 8:
            print(diff)
            num_instances(diff, True)
        diff += 1

if __name__ == '__main__':
    check_diffs()
