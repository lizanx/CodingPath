import csv
import matplotlib.pyplot as plt
from datetime import datetime

file_name = 'data/sitka_weather_2018_simple.csv'
with open(file_name) as f:
    reader = csv.reader(f)
    header = next(reader)
    print(header)

    # Get dates/temperatures from this file.
    dates, rainfalls = [], []
    for line in reader:
        dates.append(datetime.strptime(line[2], "%Y-%m-%d"))
        rainfalls.append(float(line[3]))
    # print(dates)
    # print(highs)

    # Visulization.
    plt.style.use('seaborn')
    fig, ax = plt.subplots()
    plt.title("Sitka daily rainfall amounts - 2018", fontsize=24)
    plt.xlabel('', fontsize=16)
    fig.autofmt_xdate()
    plt.ylabel('Rainfall', fontsize=16)
    plt.tick_params(axis='both', which='major', labelsize=16)

    plt.plot(dates, rainfalls, color='red')
    plt.show()


