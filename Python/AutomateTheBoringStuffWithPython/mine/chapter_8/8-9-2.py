import os, sys

if not os.path.exists('MadLibs'):
    print('MadLibs does not exits.')
    sys.exit(0)

with open('MadLibs') as mlFile:
    with open('NewMadLibs') as newMlFile:
        words = mlFile.read().split()
        newWords = []
        for word in words:
            if 'ADJECTIVE' in word:
                newWords.append(word.replace('ADJECTIVE', input('Enter an adjective:\n')))
            elif 'NOUN' in word:
                newWords.append(word.replace('NOUN', input('Enter a noun:')))
            elif 'ADVERB' in word:
                newWords.append(word.replace('ADVERB', input('Enter a adverb:')))
            elif 'VERB' in word:
                newWords.append(word.replace('VERB', input('Enter a verb:')))
            else:
                newWords.append(word)
        print(' '.join(newWords))
        newMlFile.write(' '.join(newWords))
