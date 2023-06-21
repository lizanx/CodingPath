import csv
import matplotlib.pyplot as plt
from datetime import datetime

file_name = 'data/sitka_weather_2018_simple.csv'
sitka_dates, sitka_highs, sitka_lows = [], [], []

with open(file_name) as f:
    reader = csv.reader(f)
    header = next(reader)
    print(header)

    # Get dates/temperatures from this file.
    for line in reader:
        sitka_dates.append(datetime.strptime(line[2], "%Y-%m-%d"))
        sitka_highs.append(int(line[5]))
        sitka_lows.append(int(line[6]))

file_name = 'data/death_valley_2018_simple.csv'
death_valley_dates, death_valley_highs, death_valley_lows = [], [], []
with open(file_name) as f:
    reader = csv.reader(f)
    header = next(reader)
    print(header)

    # Get dates/temperatures from this file.
    for line in reader:
        try:
            date = datetime.strptime(line[2], "%Y-%m-%d")
            high = int(line[4])
            low = int(line[5])
        except ValueError:
            print(f'Failed to get date/high/low in this line: {line}')
        else:
            death_valley_dates.append(date)
            death_valley_highs.append(high)
            death_valley_lows.append(low)

# Visulization.
plt.style.use('seaborn')
fig, ax = plt.subplots()
plt.title("Sitka/DeathValley high/low temps comparison - 2018", fontsize=20)
plt.xlabel('', fontsize=16)
fig.autofmt_xdate()
plt.ylabel('Temperature (F)', fontsize=16)
plt.tick_params(axis='both', which='major', labelsize=16)

plt.plot(sitka_dates, sitka_highs, color='red', alpha=0.5)
plt.plot(sitka_dates, sitka_lows, color='blue', alpha=0.5)
plt.fill_between(sitka_dates, sitka_highs, sitka_lows, facecolor='blue', alpha=0.1)

plt.plot(death_valley_dates, death_valley_highs, color='yellow', alpha=0.5)
plt.plot(death_valley_dates, death_valley_lows, color='green', alpha=0.5)
plt.fill_between(death_valley_dates, death_valley_highs, death_valley_lows, facecolor='green', alpha=0.1)


plt.show()
