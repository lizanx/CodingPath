from collections import Counter

words = [
    'look', 'into', 'my', 'eyes', 'look', 'into', 'my', 'eyes',
    'the', 'eyes', 'the', 'eyes', 'the', 'eyes', 'not', 'around', 'the',
    'eyes', "don't", 'look', 'around', 'the', 'eyes', 'look', 'into',
    'my', 'eyes', "you're", 'under'
]
morewords = ['why','are','you','not','looking','in','my','eyes']

words_counter = Counter(words)
print(words_counter.most_common(3))
words_counter.update(morewords)
print(words_counter)
morewords_counter = words_counter - Counter(words)
print(morewords_counter)
