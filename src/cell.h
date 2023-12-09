#ifndef __CELL_H__
#define __CELL_H__
#include <vector>
#include <string>
#include <utility>

#define DEFAULT_MOISTURE 1.0
#define MAX_MOISTURE 2.0 
#define MIN_MOISTURE 0.0

enum CellType {
    SOIL = 0,       
    ROOT = 1,       
    STONE = 2,
    NO_TYPES,      /* Number of TYPE*/ 
};

class Cell {
public: 
    std::pair<int, int> pos;
    CellType prev_type;
    CellType type;
    float moisture;
    bool is_moisture_root = false;

    // wo which root this cell belongs if it is moisture soil
    std::pair<int, int> moisture_root_pos;

    // constructor
    Cell(int x, int y);
};


#endif // __CELL_H__