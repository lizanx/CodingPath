def count_word(file, word):
    cnt = 0
    with open(file,encoding='utf-8') as f:
        for line in f:
            cnt += line.lower().count(word)
    return cnt


book_1 = "A Modest Proposal.txt"
book_2 = "Pride and Prejudice.txt"
book_3 = "The Great Gatsby.txt"

print(f"In book '{book_1}', num of 'the' = {count_word(book_1, 'the')}, num of 'the ' = {count_word(book_1, 'the ')}")

print(f"In book '{book_2}', num of 'the' = {count_word(book_2, 'the')}, num of 'the ' = {count_word(book_2, 'the ')}")

print(f"In book '{book_3}', num of 'the' = {count_word(book_3, 'the')}, num of 'the ' = {count_word(book_3, 'the ')}")