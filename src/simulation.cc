#include <chrono>
#include <thread>
#include "./simulation.h"
#include "./args.h"
#include "./macros.h"

Simulation::Simulation(Args *args_param, Grid *grid_param, Visualizer *visualizer_param) {
    this->args = args_param;
    this->grid = grid_param;
    this->visualizer = visualizer_param;

    // todo: I have force iterations for now
    // make them so they are by default height-1, and also max height-1
    this->iterations = grid_param->height - 1;
    this->rule = (Rule)args_param->rule;
}

CellType Simulation::rule_1(CellType left, CellType right) {
    // nice spaghetti code
    // cant be bothered to make it better it is 3am rn
    CellType new_cell_type;
    if (left == CellType::ROOT && right == CellType::ROOT) {
        new_cell_type = CellType::SOIL;
    }
    else if ((left == CellType::ROOT && right == CellType::SOIL) || (left == CellType::SOIL && right == CellType::ROOT)) {
        int random_number = rand() % 100 + 1;
        if (random_number <= 90) {
            new_cell_type = CellType::ROOT;
        }
        else {
            new_cell_type = CellType::SOIL;
        }
    }
    else if (left == CellType::SOIL && right == CellType::SOIL) {
        new_cell_type = CellType::SOIL;
    }
    else {
        new_cell_type = CellType::SOIL;
    }

    return new_cell_type;
}

CellType Simulation::determine_cell_type(CellType left, CellType right) {
    // we dont know wether left or right is current cell
    // just to keep that in mind

    CellType new_cell_type;
    switch(this->rule) {
        case Rule::RULE_1:
            new_cell_type = this->rule_1(left, right);
            break;
    }

    return new_cell_type;
}

void Simulation::update_grid() {
    // go thru 1 row
    this->found_root_on_row = false;
    this->planted_root = false;
    for (int x = 0; x < this->grid->width; x++) {
        // prevent out of bounds seg fault
        // todo: remove this, and do this checking shile parsing argumets
        // so u cant have more iterations then rows-1 (height -1)
        // -h = height, -i = iterations
        if (this->current_row == this->grid->height - 1) {
            return;
        }
        
        CellType current_cell = this->grid->grid[this->current_row][x].type;
        if (current_cell == CellType::STONE) { // skip if stone
            continue;
        }

        // todo: optimize this (nechaj na mna asi)
        // check to right
        if (x < this->grid->width - NEXT_CELL_TO_CHECK_POSITION) {
            CellType next_cell = this->grid->grid[this->current_row][x+NEXT_CELL_TO_CHECK_POSITION].type;
            CellType new_cell_type = this->determine_cell_type(current_cell, next_cell);
            CellType *to_change = &this->grid->grid[this->current_row+1][x+1].type;
            if (*to_change != CellType::STONE){ // never change stone
                *to_change = new_cell_type;
                if (new_cell_type == CellType::ROOT) {
                    this->planted_root = true;
                }
            }
        }

        // check left
        if (x > 1) {
            CellType prev_cell = this->grid->grid[this->current_row][x-NEXT_CELL_TO_CHECK_POSITION].type;
            CellType new_cell_type = this->determine_cell_type(prev_cell, current_cell);
            CellType *to_change = &this->grid->grid[this->current_row+1][x-1].type;
            if (*to_change != CellType::STONE){
                *to_change = new_cell_type;
                if (new_cell_type == CellType::ROOT) {
                    this->planted_root = true;
                }
            }
        }

    }
    if (!this->planted_root) {
        // if root is not planted, stop simulation
        // probably blocked by stone
        this->stop_simulation = true;
        return;
    }
}

void Simulation::run() {
    // reset file, isnt there better way?
    this->visualizer->data_file.open(Const::DATA_FILE_PATH);
    this->visualizer->data_file.close();

    this->grid->place_stones();
    this->grid->place_root();

    for (int i = 0; i < this->iterations; i++) {
        this->visualizer->draw_grid(this->grid);
        this->update_grid();
        this->current_row++;

        if (this->stop_simulation) {
            break;
        }
    }
}