// Implementation of celluar automata
// authors: Tomas Fratrik (xfratr01), Patrik Jezko (xjesko01)
#include "./cell.h"

Cell::Cell(int x, int y) {
    this->type = CellType::SOIL;
    this->prev_type = this->type;
    this->pos = std::make_pair(x, y);
    this->moisture = DEFAULT_MOISTURE;
    this->moisture_root_pos = std::make_pair(-1, -1);
    this->rootx = x;
    this->rooty = y;
}