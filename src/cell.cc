#include "./cell.h"

Cell::Cell(int x, int y) {
    this->type = CellType::SOIL;
    this->prev_type = this->type;
    this->pos = std::make_pair(x, y);
    this->moisture = DEFAULT_MOISTURE;
}