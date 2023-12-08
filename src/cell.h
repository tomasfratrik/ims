#ifndef __CELL_H__
#define __CELL_H__
#include <vector>
#include <string>
#include <utility>

#define DEFAULT_MOISTURE 1
#define MAX_MOISTURE 2 
#define MIN_MOISTURE 0

enum CellType {
    SOIL = 0,       
    ROOT = 1,       
    STONE = 2 ,
    NO_TYPES,      /* Number of TYPE*/ 
};

class Cell {
public: 
    std::pair<int, int> pos;
    CellType prev_type;
    CellType type;
    float moisture;

    // constructor
    Cell(int x, int y);
};


#endif // __CELL_H__