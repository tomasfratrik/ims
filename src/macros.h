#ifndef __MACROS_H__
#define __MACROS_H__

#ifdef DEBUG
#define DEBUG(...) do { fprintf( stderr, "[DBG]: %s\n", __VA_ARGS__ ); } while(0)
#else
#define DEBUG(...) do {} while (0)
#endif // DEBUG

// this are common amongst rules
#define BOTH_ROOTS left->type == CellType::ROOT && right->type == CellType::ROOT
#define BOTH_SOILS left->type == CellType::SOIL && right->type == CellType::SOIL
#define ONE_ROOT_ONE_SOIL (left->type == CellType::ROOT && right->type == CellType::SOIL) || (left->type == CellType::SOIL && right->type == CellType::ROOT)

#endif // __MACROS_H__