

def sed(old, new, fin, fout):
    try:
        file_object = open(fin, encoding='UTF-8')
    except:
        print('Failed to open', fin)
        content = []
    else:
        content = file_object.readlines()
        file_object.close()
    i = 0
    while i < len(content):
        if old in content[i]:
            content[i] = content[i].replace(old, new)
        i += 1
    try:
        file_object = open(fout, 'w', encoding='UTF-8')
    except:
        print('Failed to open', fout)
    else:
        for line in content:
            file_object.write(line)
        file_object.close()


if __name__ == '__main__':
    sed('me', 'ME', 'test.txt', 'result.txt')