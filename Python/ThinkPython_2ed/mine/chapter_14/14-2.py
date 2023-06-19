import shelve

from anagram_sets import signature, all_anagrams

def store_anagrams(filename, anagram_map):
    shelf = shelve.open(filename, 'c')
    for anagram, words_list in anagram_map.items():
        shelf[anagram] = words_list
    shelf.close()

def read_anagrams(filename, anagram):
    shelf = shelve.open(filename)
    res = shelf[anagram]
    shelf.close()
    return res


if __name__ == '__main__':
    anagram_map = all_anagrams('words.txt')
    store_anagrams('anagram_store', anagram_map)
    print(read_anagrams('anagram_store', 'ekl'))