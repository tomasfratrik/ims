
#ifndef __VISUALIZER_H__
#define __VISUALIZER_H__
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "./cell.h"
#include "./args.h"
#include "./const.h"
#include "./grid.h"

class Visualizer {
    public:
        bool no_color_flg = false;
        bool visulize_stdout_flg = false;
        int width = 0;
        int height = 0;
        std::string cell_symbol;
        std::ofstream data_file;

        // constructor
        Visualizer(Grid *grid);
        void draw(Grid grid);
        void draw_grid(Grid *grid);
        void draw_cell(Grid *grid, int x, int y);
};

#endif // __VISUALIZER_H__