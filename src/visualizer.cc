#include <iostream>
#include <fstream>
#include "./visualizer.h"

Visualizer::Visualizer(Args args) {
    this->width = args.width;
    this->height = args.height;
    this->no_color_flg = args.no_color_flg;
    this->visulize_stdout_flg = args.visulize_stdout_flg;
    if (!visulize_stdout_flg) {
        this->no_color_flg = true;
    }

    if (args.cell_symb == "default") {
        this->cell_symbol = Const::DEFAULT_CELL_SYMB;
    } 
    else if (args.cell_symb == "dot") {
        this->cell_symbol = Const::DOT;
    }
    else if (args.cell_symb == "square") {
        this->cell_symbol = Const::SMALL_SQUARE;
    }
    else {
        this->cell_symbol = Const::DEFAULT_CELL_SYMB;
    }

}

void Visualizer::draw(std::vector<std::vector<int>> grid) {
    std::ofstream data_file("./data/data.txt", std::ios::app);
    std::string color;
    for(int i = 0; i < this->height; i++) {
        for(int j = 0; j < this->width; j++) {
            std::string state;
            switch(grid[i][j]) {
                case CellState::DEAD:
                    this->no_color_flg ? state = "." : state = Const::WHITE + this->cell_symbol + Const::RESET;
                    break;
                case CellState::ALIVE:
                    this->no_color_flg ? state = "@" : state = Const::GREEN + this->cell_symbol + Const::RESET;
                    break;
                case CellState::MID:
                    this->no_color_flg ? state = "X" : state = Const::RED + this->cell_symbol + Const::RESET;
                    break;
                default:
                    // todo
                    std::cout << "VIS ERROR:"<< grid[i][j] << std::endl;
                    exit(1);
            }

            data_file << state; //write state to file

            if (visulize_stdout_flg){
                std::cout << state;
            }
        }
        data_file << std::endl; //write newline to file

        if (visulize_stdout_flg){
            std::cout << std::endl;
        }
    }

    data_file << std::endl; //separate grids
    data_file.close();
}