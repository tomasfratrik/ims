#include <chrono>
#include <thread>
#include "./simulation.h"
#include "./args.h"
#include "./macros.h"

Simulation::Simulation(Args *args_param, Grid *grid_param, Visualizer *visualizer_param) {
    this->args = args_param;
    this->grid = grid_param;
    this->visualizer = visualizer_param;

    this->iterations = args_param->iterations;
    this->rule = (Rule)args_param->rule;
    this->moisture = args_param->moisture;
}

float Simulation::calculate_moisture(int base) {
    // float new_base = base * this->moisture;  
    // if (new_base > 100) new_base = 100;
    // if (new_base < 0) new_base = 0;
    // return new_base;
    return base;
}

CellType Simulation::root_if_hit(int percentage) {
    int random_number = rand() % 100 + 1;
    if (random_number <= this->calculate_moisture(percentage)) {
        return CellType::ROOT;
    }
    else {
        return CellType::SOIL;
    }
}

CellType Simulation::cond_1() {
    CellType new_cell_type;
    if(this->rule == Rule::RULE_4){
        new_cell_type = CellType::ROOT;
    }
    else if (this->rule == Rule::RULE_3){
        new_cell_type = this->root_if_hit(70);
    }
    else {
        new_cell_type = CellType::SOIL;
    }
    return new_cell_type;
}

CellType Simulation::cond_2() {
    CellType new_cell_type;
    if(this->rule == Rule::RULE_1){
        new_cell_type = this->root_if_hit(90);
    }
    else if (this->rule == Rule::RULE_2){
        new_cell_type = this->root_if_hit(70);
    }
    else {
        new_cell_type = this->root_if_hit(60);
    }
    return new_cell_type;
}
CellType Simulation::cond_4() {
    CellType new_cell_type;
    return CellType::SOIL;
}

CellType Simulation::determine_cell_type(CellType left, CellType right) {
    // we dont know wether left or right is current cell
    // just to keep that in mind

    CellType new_cell_type;
    if (BOTH_ROOTS) {
        new_cell_type = this->cond_1();
    }
    else if (ONE_ROOT_ONE_SOIL) {
        new_cell_type = this->cond_2();
    }
    else if (BOTH_SOILS) {
        new_cell_type = this->cond_4();
    }
    else { // presence of stone or smth else
        new_cell_type = CellType::SOIL;
    }
    return new_cell_type;
}

void Simulation::update_grid() {
    // go thru 1 row
    this->found_root_on_row = false;
    this->planted_root = false;
    for (int x = 0; x < this->grid->width; x++) {
        // prevent out of bounds seg fault
        
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

    // this->grid->place_stones();
    this->grid->place_moisture_roots();
    this->grid->expand_moisture();
    // this->grid->place_root();

    for (int i = 0; i < this->iterations; i++) {
        this->visualizer->draw_grid(this->grid);
        this->update_grid();
        this->current_row++;

        if (this->stop_simulation) {
            break;
        }
    }
}