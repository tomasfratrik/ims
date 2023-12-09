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

void Grid::expand_moisture_root(Cell *moisture_root) {

    std::vector<Cell*> open_list;
    std::vector<Cell*> close_list;
    open_list.push_back(moisture_root);

    float step = 0.1;

    while(!open_list.empty()) {
        Cell *current_cell = open_list.back();
        open_list.pop_back();
        close_list.push_back(current_cell);
        int x = current_cell->pos.first;
        int y = current_cell->pos.second;
        if (y - 1 >= 0) {
            Cell *cell_ptr_up = &this->grid[y - 1][x];
            // if cell_ptr_up is in the close list vector skip it
            if (this->is_cell_in_vector(cell_ptr_up, close_list)) {
                cell_ptr_up->moisture += (current_cell->moisture - step) - 1 ;
                open_list.push_back(cell_ptr_up);
            }
        }
        if (y + 1 < this->height) {
        }
        if (x - 1 >= 0) {
        }
        if (x + 1 < this->width) {
        }
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