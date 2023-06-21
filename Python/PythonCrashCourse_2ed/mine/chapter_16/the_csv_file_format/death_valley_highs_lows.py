import csv
import matplotlib.pyplot as plt
from datetime import datetime

file_name = 'data/death_valley_2018_simple.csv'
with open(file_name) as f:
    reader = csv.reader(f)
    header = next(reader)
    print(header)

    # Get dates/temperatures from this file.
    dates, highs, lows = [], [], []
    for line in reader:
        try:
            date = datetime.strptime(line[2], "%Y-%m-%d")
            high = int(line[4])
            low = int(line[5])
        except ValueError:
            print(f'Failed to get date/high/low in this line: {line}')
        else:
            dates.append(date)
            highs.append(high)
            lows.append(low)
    # print(dates)
    # print(highs)

    # Visulization.
    plt.style.use('seaborn')
    fig, ax = plt.subplots()
    plt.title("Daily high and low temperatures - 2018\nDeath Valley, CA", fontsize=20)
    plt.xlabel('', fontsize=16)
    fig.autofmt_xdate()
    plt.ylabel('Temperature (F)', fontsize=16)
    plt.tick_params(axis='both', which='major', labelsize=16)

    plt.plot(dates, highs, color='red', alpha=0.5)
    plt.plot(dates, lows, color='blue', alpha=0.5)
    plt.fill_between(dates, highs, lows, facecolor='blue', alpha=0.1)
    plt.show()

