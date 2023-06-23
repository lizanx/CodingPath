def print_grid(grid: list):
    if not grid or any(len(e) != len(grid[0]) for e in grid):
        raise ValueError('Invalid input grid.')

    for col in range(len(grid[0])):
        for row in range(len(grid)):
            print(grid[row][col], end='')
        print()
