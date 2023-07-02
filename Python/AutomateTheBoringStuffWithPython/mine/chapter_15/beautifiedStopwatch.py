import time, pyperclip

print('Press "Enter" to start, then each "Enter" denotes a record, and "CTRL-C" means termination.')
input()

startTime = time.time()
lastTime = startTime
recordCount = 1
records = []

try:
    while True:
        input()
        recordTime = time.time()
        sinceLastRecord = recordTime - lastTime
        sinceStart = recordTime - startTime
        record = f'Record #{str(recordCount).rjust(3)}: {str(round(sinceStart, 2)).rjust(6)} ({str(round(sinceLastRecord, 2)).rjust(6)})'
        records.append(record)
        print(record, end='')
        lastTime = recordTime
        recordCount += 1
except KeyboardInterrupt:
    pyperclip.copy('\n'.join(records))
    print('\nDone.')
