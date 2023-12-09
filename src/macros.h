#ifndef __MACROS_H__
#define __MACROS_H__

#ifdef DEBUG
#define DEBUG(...) do { fprintf( stderr, "[DBG]: %s\n", __VA_ARGS__ ); } while(0)
#else
#define DEBUG(...) do {} while (0)
#endif // DEBUG

// this are common amongst rules
#define BOTH_ROOTS left == CellType::ROOT && right == CellType::ROOT
#define BOTH_SOILS left == CellType::SOIL && right == CellType::SOIL
#define ONE_ROOT_ONE_SOIL (left == CellType::ROOT && right == CellType::SOIL) || (left == CellType::SOIL && right == CellType::ROOT)

#endif // __MACROS_H__