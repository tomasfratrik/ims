#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include "./visualizer.h"

Visualizer::Visualizer(Grid *grid) {
    this->width = grid->width;
    this->height = grid->height;
    this->no_color_flg = grid->no_color_flg;
    this->visulize_stdout_flg = grid->visulize_stdout_flg;
    if (!visulize_stdout_flg) {
        this->no_color_flg = true;
    }

    if (grid->cell_symb == "default") {
        this->cell_symbol = Const::DEFAULT_CELL_SYMB;
    } 
    else if (grid->cell_symb == "dot") {
        this->cell_symbol = Const::DOT;
    }
    else if (grid->cell_symb == "square") {
        this->cell_symbol = Const::SMALL_SQUARE;
    }
    else {
        this->cell_symbol = Const::DEFAULT_CELL_SYMB;
    }

}
void Visualizer::draw_grid(Grid *grid) {
    this->data_file.open(Const::DATA_FILE_PATH, std::ios::app);

    /* always clear screen to draw new grid if -v */
    if (visulize_stdout_flg){
        std::cout << Const::CLEAR_SCREEN;
    }

    /* Go thru each cell and decide*/
    for(int y = 0; y < this->height; y++) {
        for(int x = 0; x < this->width; x++) {
            this->draw_cell(grid, x, y);
        }
        this->data_file << std::endl; 
        if (visulize_stdout_flg){
            std::cout << std::endl;
        }
    }

    this->data_file << std::endl; //separate grids
    if (visulize_stdout_flg){
        std::cout << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(grid->timeout));
    }
    this->data_file.close();


}
void Visualizer::draw_cell(Grid *grid, int x, int y) {
    std::string color_symbol;
    std::string ascii_symbol;
    float m = grid->grid[y][x].moisture;

    switch(grid->grid[y][x].type) {
        case CellType::SOIL:
            // color_symbol = Const::WHITE;
            // check moisture 1-2
            if (m <= 1) {
                color_symbol = Const::WHITE;
                ascii_symbol = ".";
            }
            else if (m <= 1.29) {
                color_symbol = Const::SKY_BLUE;
                ascii_symbol = "1";
            }
            else if (m <= 1.49) {
                color_symbol = Const::CYAN;
                ascii_symbol = "2";
            }
            else if (m <= 1.69) {
                color_symbol = Const::LIGHT_BLUE;
                ascii_symbol = "3";
            }
            else {
                color_symbol = Const::BLUE;
                ascii_symbol = "4";
            }
       
            break;
        case CellType::ROOT:
            color_symbol = Const::BLACK;
            ascii_symbol = "@";
            break;
        case CellType::STONE:
            color_symbol = Const::RED;
            ascii_symbol = "X";
            break;
        default:
            // std::cout << "VIS ERROR:"<< grid.grid[y][x].type << std::endl;
            exit(1);
    }

    this->data_file << ascii_symbol;

    /* print to stdout if -v */
    if (visulize_stdout_flg){
        if (this->no_color_flg) {
            color_symbol = "";
        }
        else {
            ascii_symbol = this->cell_symbol;
        }
        std::cout << color_symbol << ascii_symbol << Const::RESET;
    }
}