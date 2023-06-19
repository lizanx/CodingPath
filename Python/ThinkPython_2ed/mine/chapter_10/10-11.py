def is_reverse_pair(s1, s2):
    return s1 == s2[::-1]

if __name__ == '__main__':
    content = []
    with open("words.txt") as fin:
        for word in fin:
            content.append(word.strip())
    # for i in range(len(content) - 1):
    #     for j in range(i + 1, len(content)):
    #         if is_reverse_pair(content[i], content[j]):
    #             print(content[i], content[j])
    for word in content:
        if word != word[::-1] and word[::-1] in content:
            print(word, word[::-1])