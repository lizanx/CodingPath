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
    station, name = None, None
    for line in reader:
        try:
            date = datetime.strptime(line[header.index('DATE')], "%Y-%m-%d")
            high = int(line[header.index('TMAX')])
            low = int(line[header.index('TMIN')])
        except ValueError:
            print(f'Failed to get date/high/low in this line: {line}')
        else:
            dates.append(date)
            highs.append(high)
            lows.append(low)
            if not station or not name:
                station = line[header.index('STATION')]
                name = line[header.index('NAME')]

    # Visulization.
    plt.style.use('seaborn')
    fig, ax = plt.subplots()
    plt.title(f"Daily high and low temperatures - 2018\n{name}, {station}", fontsize=20)
    plt.xlabel('', fontsize=16)
    fig.autofmt_xdate()
    plt.ylabel('Temperature (F)', fontsize=16)
    plt.tick_params(axis='both', which='major', labelsize=16)

    plt.plot(dates, highs, color='red', alpha=0.5)
    plt.plot(dates, lows, color='blue', alpha=0.5)
    plt.fill_between(dates, highs, lows, facecolor='blue', alpha=0.1)
    plt.show()

