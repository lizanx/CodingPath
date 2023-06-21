import matplotlib.pyplot as plt

from die import Die

if __name__ == '__main__':
    die_1 = Die()
    die_2 = Die()
    results = [(die_1.roll() + die_2.roll()) for n in range(0, 5000)]
    max_result = die_1.num_sides + die_2.num_sides
    frequencies = [results.count(value) for value in range(2, max_result + 1)]

    # Visualization
    fig, ax = plt.subplots()
    plt.style.use('seaborn')
    ax.set_title('Frequencies of tossing two 6Ds')
    ax.set_xlabel('Result')
    ax.set_ylabel('Frequency')
    ax.plot(list(range(2, max_result + 1)), frequencies, linewidth=2)
    plt.show()

