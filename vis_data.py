#!/usr/bin/env python3
import sys
from matplotlib import pyplot as plt
from matplotlib import animation
from matplotlib.colors import ListedColormap
from matplotlib.animation import FuncAnimation
from matplotlib.colors import LinearSegmentedColormap
from IPython import display
import numpy as np
import argparse


fig, ax = plt.subplots()

def add_frame(grid):
    ax.clear()
    data = np.zeros_like(grid, dtype=float)  # Initialize empty array of same shape as grid with float data type
    for i, row in enumerate(grid):
        for j, symbol in enumerate(row):
            data[i, j] = float(symbol)
    
    cmap = plt.cm.colors.ListedColormap(['#bf8040', 'green', 'grey','#ac7339' ,'#996633','#86592d' , '#604020'] )
    bounds = [0, 1, 2, 3, 4, 5, 6, 7]
    norm = plt.cm.colors.BoundaryNorm(bounds, cmap.N)

    ax.imshow(data, cmap=cmap, norm=norm, interpolation='nearest')

    plt.pause(0.01)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-f", "--file", type=str, help="Specify the file path", default="data/data.txt")
    parser.add_argument("-g", "--gif", type=str, help="Specify the gif path", default="data/animation.gif")
    args = parser.parse_args()

    file_path = args.file
    gif_path = args.gif

    with open(file_path, 'r') as file:
        lines = file.readlines()

    # At the start of the file there is the whole grid, then a blank line
    # and after this there are no grids, just rows, and we update the grid by the rows
    starting_grid = []

    # Parse grid
    lines_read = 0
    for line in lines:
        lines_read += 1
        line = line.strip()
        if line:
            starting_grid.append([int(c) for c in line])
        else:
            add_frame(starting_grid)
            break
    
    frames = [starting_grid]
    lines = lines[lines_read:]
    buffer_grid = starting_grid

    cmap = plt.cm.colors.ListedColormap(['#bf8040', 'green', 'grey','#ac7339' ,'#996633','#86592d' , '#604020'] )
    bounds = [0, 1, 2, 3, 4, 5, 6, 7]
    norm = plt.cm.colors.BoundaryNorm(bounds, cmap.N)

    current_row = 0
    for line in lines:
        line = line.strip()
        if line:
            buffer_grid[current_row] = [int(c) for c in line]
            current_row += 1
            add_frame(buffer_grid)
            frames.append([row.copy() for row in buffer_grid])

    num_frames = len(frames)
    interval = 100
    animation_fig, animation_ax = plt.subplots()
    im = animation_ax.imshow(frames[0], cmap=cmap, norm=norm)

    def update_frame(i):
        im.set_data(frames[i])

    ani = animation.FuncAnimation(
        animation_fig, update_frame, frames=num_frames,
        interval=interval, repeat=False
    )

    # Save animation as a GIF file
    output_file = gif_path
    ani.save(output_file, writer='pillow')
    print(f"Saved animation as '{output_file}'")

    # plt.show()