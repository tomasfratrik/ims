#ifndef __ARGS_H__
#define __ARGS_H__

#include <string>
#include "./grid.h"

#define DEFAULT_WIDTH 30
#define DEFAULT_HEIGHT 30
#define DEFAULT_TIMEOUT 1000
#define STONE_PROBABILITY 0

class Args{
public:
    int width = DEFAULT_WIDTH;
    int height = DEFAULT_HEIGHT;
    int timeout = DEFAULT_TIMEOUT;
    bool no_color_flg = false;
    bool visulize_stdout_flg = false;
    std::string cell_symb = "default";
    int stone_probability = STONE_PROBABILITY;

    // constructors
    Args(int argc, char **argv);
};

#endif // __ARGS_H__
