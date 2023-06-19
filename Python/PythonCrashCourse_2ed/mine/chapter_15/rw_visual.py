import matplotlib.pyplot as plt

from random_walk import RandomWalk

if __name__ == '__main__':
    while True:
        rw = RandomWalk(50_000)
        rw.fill_walk()
        
        fig, ax = plt.subplots(figsize=(12, 7))
        plt.style.use('seaborn')
        ax.scatter(rw.x_values, rw.y_values, s=1,
                c=range(rw.num_points), cmap=plt.cm.Blues, edgecolors='none')
        # Emphasize the first and last points.
        ax.scatter(rw.x_values[0], rw.y_values[0], s=100, c='green', edgecolors='none')
        ax.scatter(rw.x_values[-1], rw.y_values[-1], s=100, c='red', edgecolors='none')
        # Hide the axes.
        ax.get_xaxis().set_visible(False)
        ax.get_yaxis().set_visible(False)
        plt.show()

        keep_running = input('Make another walk? (y/n)')
        if keep_running == 'n':
            break


