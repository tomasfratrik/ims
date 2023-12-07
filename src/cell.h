#ifndef __CELL_H__
#define __CELL_H__

enum CellState {
    DEAD = 0,       /* Cell is dead */
    ALIVE = 1,      /* Cell is alive */
    MID = 2,
    NO_STATES,      /* Number of States */ 
};

#endif // __CELL_H__