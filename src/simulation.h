#ifndef __SIMULATION_H__
#define __SIMULATION_H__


#include "./args.h"
#include "./visualizer.h"
#include "./const.h"

#define NEXT_CELL_TO_CHECK_POSITION 2

enum Rule {
    RULE_1 = 1,
    RULE_2 = 2,
    RULE_3 = 3,
    RULE_4 = 4,
    NO_RULES,       /* Number of RULES */ 
};

class Simulation {
public:
    Args *args;
    Grid *grid;
    Visualizer *visualizer;


    int iterations;
    int current_row = 0;
    Rule rule;

    // constructor
    Simulation(Args *args_param, Grid *grid_param, Visualizer *visualizer_param);
    CellType determine_cell_type(CellType left, CellType right);
    void update_grid();
    void run();
};

#endif // __SIMULATION_H__