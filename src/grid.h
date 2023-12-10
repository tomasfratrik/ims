// Implementation of celluar automata
// authors: Tomas Fratrik (xfratr01), Patrik Jezko (xjesko01)
#ifndef __GRID_H__
#define __GRID_H__

class Args;

#include <vector>
#include <string>
#include "./cell.h"
#include "./args.h"

class Grid {
public:
    int width;
    int height;
    int timeout;
    bool no_color_flg;
    bool visulize_stdout_flg;
    std::string cell_symb;
    int stone_probability;
    int moisture_roots_to_plant;
    float moisture;

    std::vector<std::vector<Cell>> grid;

    // constructor
    Grid(Args args);
    void init_grid();
    void place_stones();
    void place_root();
    
    // place 1x1 pixel roots by -p param
    void place_moisture_roots();
    // expand moisture roots
    void expand_moisture();

    // util functions
    bool cells_have_same_moisture_root(Cell *cell_1, Cell *cell_2);
    // expand moistre root
    void expand_moisture_root(Cell *moisture_root);
    void expand_moisture_cell(Cell *cell);

};


#endif // __GRID_H__