import matplotlib.pyplot as plt

from random_walk import RandomWalk

if __name__ == '__main__':
    while True:
        rw = RandomWalk(50_000)
        rw.fill_walk()
        
        fig, ax = plt.subplots(figsize=(12, 7))
        plt.style.use('seaborn')
        ax.plot(rw.x_values, rw.y_values, linewidth=1)
        # Hide the axes.
        ax.get_xaxis().set_visible(False)
        ax.get_yaxis().set_visible(False)
        plt.show()

        keep_running = input('Make another walk? (y/n)')
        if keep_running == 'n':
            break


