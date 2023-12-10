#include <iostream>
#include "./grid.h"
#include "./args.h"

Grid::Grid(Args args) {
    this->width = args.width;
    this->height = args.height;
    this->timeout = args.timeout;
    this->stone_probability = args.stone_probability;
    this->moisture_roots_to_plant = args.moisture_roots_to_plant;
    this->moisture = args.moisture;
    this->no_color_flg = args.no_color_flg;
    this->visulize_stdout_flg = args.visulize_stdout_flg;
    this->cell_symb = args.cell_symb;
    Grid::init_grid();
}

void Grid::init_grid() {
    for (int y = 0; y < this->height; y++) {
        std::vector<Cell> row;
        for (int x = 0; x < this->width; x++) {
            Cell cell(x,y);
            row.push_back(cell);
        }
        this->grid.push_back(row);
    }
}

void Grid::place_root() {
    this->grid[0][this->width / 2].type = CellType::ROOT;
}

void Grid::place_moisture_roots() {
    // todo: check if ( height * width > moisture_roots_to_plant)
    for (int i = 0; i < this->moisture_roots_to_plant; i++) {
        int random_height = rand() % this->height;
        int random_width = rand() % this->width;

        if (this->grid[random_height][random_width].is_moisture_root ||
            random_height == 0 ) {
            // try again
            i--;
            continue;
        }

        this->grid[random_height][random_width].is_moisture_root = true;
        this->grid[random_height][random_width].moisture = this->moisture;
        this->grid[random_height][random_width].moisture_root_pos = std::make_pair(random_height, random_width);
    }
}
bool Grid::is_cell_in_vector(Cell *cell, std::vector<Cell*> vector_list) {
    int x = cell->pos.first;
    int y = cell->pos.second;
    for (int i = 0; i < vector_list.size(); i++) {
        if (vector_list[i]->pos.first == x && vector_list[i]->pos.second == y) {
            return true;
        }
    }
    return false;
}


bool isWaterRootsChild(int rootx, int rooty, int x, int y){
    return (rootx == x && rooty == y);
}

void Grid::expand_moisture_root(Cell *moisture_root) {

    float excess_moisture = moisture_root->moisture - 1.0;
    int steps = static_cast<int>(excess_moisture * 10);
    float set_moisture = excess_moisture - 0.1;
    int x = moisture_root->pos.first;
    int y = moisture_root->pos.second;

    for (int i = 1; i <= steps; i++) {
        for (int j = -i; j <= i; j++) {
            int new_y = y - i;
            int new_x = x + j;

            if (new_y >= 0 && new_y < height && new_x >= 0 && new_x < width && !grid[new_y][new_x].is_moisture_root && !isWaterRootsChild(grid[new_y][new_x].rootx, grid[new_y][new_x].rooty, x, y)) {
                grid[new_y][new_x].moisture = std::min(2.0f, grid[new_y][new_x].moisture + set_moisture);
                grid[new_y][new_x].rootx = x;
                grid[new_y][new_x].rooty = y;
            }

            new_y = y + i;
            new_x = x + j;

            if (new_y >= 0 && new_y < height && new_x >= 0 && new_x < width && !grid[new_y][new_x].is_moisture_root && !isWaterRootsChild(grid[new_y][new_x].rootx, grid[new_y][new_x].rooty, x, y)) {
                grid[new_y][new_x].moisture = std::min(2.0f, grid[new_y][new_x].moisture + set_moisture);
                grid[new_y][new_x].rootx = x;
                grid[new_y][new_x].rooty = y;
            }

            new_y = y + j;
            new_x = x - i;

            if (new_y >= 0 && new_y < height && new_x >= 0 && new_x < width && !grid[new_y][new_x].is_moisture_root && !isWaterRootsChild(grid[new_y][new_x].rootx, grid[new_y][new_x].rooty, x, y)) {
                grid[new_y][new_x].moisture = std::min(2.0f, grid[new_y][new_x].moisture + set_moisture);
                grid[new_y][new_x].rootx = x;
                grid[new_y][new_x].rooty = y;
            }

            new_y = y + j;
            new_x = x + i;

            if (new_y >= 0 && new_y < height && new_x >= 0 && new_x < width && !grid[new_y][new_x].is_moisture_root && !isWaterRootsChild(grid[new_y][new_x].rootx, grid[new_y][new_x].rooty, x, y)) {
                grid[new_y][new_x].moisture = std::min(2.0f, grid[new_y][new_x].moisture + set_moisture);
                grid[new_y][new_x].rootx = x;
                grid[new_y][new_x].rooty = y;
            }
        }
        set_moisture -= 0.1;
    }

}


void Grid::expand_moisture() {
    for (int y = 0; y < this->height; y++) {
        for (int x = 0; x < this->width; x++) {
            Cell *cell_ptr = &this->grid[y][x];
            if (cell_ptr->is_moisture_root) {
                this->expand_moisture_root(cell_ptr); 
            }
        }
    }

}

void Grid::place_stones() {
    /**
     * Go thru each cell and with
     * percentage probability place a stone -> change cell
     * type to STONE
     * 
     */

    for (int y = 0; y < this->height; y++) {
        for (int x = 0; x < this->width; x++) {
            int random = rand() % 100 + 1;
            if (random <= this->stone_probability) {
                this->grid[y][x].type = CellType::STONE;
            }
        }
    }
}