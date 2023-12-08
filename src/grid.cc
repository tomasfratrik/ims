#include "./grid.h"
#include "./args.h"

Grid::Grid(Args args) {
    this->width = args.width;
    this->height = args.height;
    this->timeout = args.timeout;
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