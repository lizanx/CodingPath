def draw_grid(gird_rows, grid_cols, size):
    if gird_rows <= 0 or grid_cols <= 0 or size <= 0:
        print("Invalid parameters!")
        return
    rows, cols = gird_rows * (size + 1) + 1, grid_cols * (size + 1) + 1
    for row in range(rows):
        for col in range(cols):
            if row % (size + 1) == 0:
                if col % (size + 1) == 0:
                    print('+ ', end='')
                else:
                    print('- ', end='')
            else:
                if col % (size + 1) == 0:
                    print('| ', end='')
                else:
                    print('  ', end='')
        print()

if __name__ == '__main__':
    print("2x2 grid:")
    draw_grid(2, 2, 4)
    print("\n\n4x4 grid:")
    draw_grid(4, 4, 4)
