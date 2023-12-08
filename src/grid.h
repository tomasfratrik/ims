#ifndef __GRID_H__
#define __GRID_H__

class Args;

#include <vector>
#include <string>
#include "./cell.h"


class Grid {
public:
    int width;
    int height;
    int timeout;
    bool no_color_flg;
    bool visulize_stdout_flg;
    std::string cell_symb;
    int stone_probability;

    std::vector<std::vector<Cell>> grid;

    // constructor
    Grid(Args args);
    void init_grid();
    void place_stones();
    void place_root();

};


#endif // __GRID_H__