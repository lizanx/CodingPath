import matplotlib.pyplot as plt
from random import choice

class RandomWalk:
    """A class to generate random walks."""

    def __init__(self, num_points=5000):
        """Initialize attributes of the walk."""
        self.num_points = num_points
        self.x_values = [0]
        self.y_values = [0]

    def _get_step(self, step_range=(0, 1, 2, 3, 4, 5)):
        return choice((-1,1)) * choice(step_range)

    def fill_walk(self):
        """Calculate all points in the walk."""
        while len(self.x_values) < self.num_points:
            x_step = self._get_step()
            y_step = self._get_step()
            if x_step == 0 and y_step == 0:
                continue
            # Calculate and store the new position
            x_pos = self.x_values[-1] + x_step
            y_pos = self.y_values[-1] + y_step
            self.x_values.append(x_pos)
            self.y_values.append(y_pos)


if __name__ == '__main__':
    plt.style.use('ggplot')
    fig, ax = plt.subplots()
    rw = RandomWalk()
    rw.fill_walk()
    ax.scatter(rw.x_values, rw.y_values, s=10)
    plt.show()
