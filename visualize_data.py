#!/usr/bin/env python3
import numpy as np
import matplotlib.pyplot as plt




if __name__ == "__main__":
    file_path = 'data/data.txt'
    with open(file_path, 'r') as file:
        lines = file.readlines()

    grids = []
    grid = []
    for line in lines:
        line = line.strip()
        if line:
            grid.append([c for c in line])
        elif grid:
            grids.append(grid)
            grid = []

    # Add the last grid if it is not empty
    if grid:
        grids.append(grid)

    fig, ax = plt.subplots()

    for grid in grids:
        data = np.zeros_like(grid, dtype=float)  # Initialize empty array of same shape as grid with float data type

        for i, row in enumerate(grid):
            for j, symbol in enumerate(row):
                if symbol == '.':
                    data[i, j] = 1.0  # '.' is white
                elif symbol == '@':
                    data[i, j] = 0.0  # '@' is black
                elif symbol == 'X':
                    data[i, j] = 2.0  # 'X' is blue

        cmap = plt.cm.colors.ListedColormap(['black', 'white', 'red'])
        bounds = [0, 1, 2, 3]
        norm = plt.cm.colors.BoundaryNorm(bounds, cmap.N)

        ax.imshow(data, cmap=cmap, norm=norm, interpolation='nearest')

        # in seconds
        # so 0.05 is 50ms
        plt.pause(0.001)

    plt.show()
