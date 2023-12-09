#include <chrono>
#include <thread>
#include "./simulation.h"
#include "./args.h"
#include "./macros.h"

Simulation::Simulation(Args *args_param, Grid *grid_param, Visualizer *visualizer_param) {
    this->args = args_param;
    this->grid = grid_param;
    this->visualizer = visualizer_param;
    // this->iterations = args_param->iterations;
    this->iterations = grid_param->height - 1;
    this->rule = (Rule)args_param->rule;
}

CellType Simulation::determine_cell_type(CellType left, CellType right) {
    CellType new_cell_type;
    // both root -> soil
    // one of them is root and other is soil -> 90% root, 10% soil
    // both soil -> soil
    // one of them rock -> soil

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
    else if ((left == CellType::STONE && right == CellType::SOIL) || (left == CellType::SOIL && right == CellType::STONE)) {
        new_cell_type = CellType::SOIL;
    }
    else {
        new_cell_type = CellType::SOIL;
    }

    return new_cell_type;
}

void Simulation::update_grid() {
    // go thru 1 row
    for (int x = 0; x < this->grid->width; x++) {
        CellType current_cell = this->grid->grid[this->current_row][x].type;

        // check to right
        if (x < this->grid->width - NEXT_CELL_TO_CHECK_POSITION) {
            CellType next_cell = this->grid->grid[this->current_row][x+NEXT_CELL_TO_CHECK_POSITION].type;
            CellType new_cell_type = this->determine_cell_type(current_cell, next_cell);
            this->grid->grid[this->current_row+1][x+1].type = new_cell_type;
        }

        // check left
        if (x > 1) {
            CellType prev_cell = this->grid->grid[this->current_row][x-NEXT_CELL_TO_CHECK_POSITION].type;
            CellType new_cell_type = this->determine_cell_type(prev_cell, current_cell);
            this->grid->grid[this->current_row+1][x-1].type = new_cell_type;
        }
    }
}

void Simulation::run() {
    // reset file
    this->visualizer->data_file.open(Const::DATA_FILE_PATH);
    this->visualizer->data_file.close();

    this->grid->place_stones();
    this->grid->place_root();
    this->visualizer->draw_grid(*this->grid);

    // optimized and max iterations are height-1
    for (int i = 0; i < this->iterations; i++) {
        this->update_grid();
        this->visualizer->draw_grid(*this->grid);

        // if -v flag is not set, we don't want to wait
        if (this-grid->visulize_stdout_flg) {
            std::this_thread::sleep_for(std::chrono::milliseconds(this->grid->timeout));
        }
        this->current_row++;
    }

}