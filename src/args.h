// Implementation of celluar automata
// authors: Tomas Fratrik (xfratr01), Patrik Jezko (xjesko01)

#ifndef __ARGS_H__
#define __ARGS_H__

#include <string>
#include "./cell.h"

#define DEFAULT_WIDTH 30
#define DEFAULT_HEIGHT 30
#define DEFAULT_TIMEOUT 1000
#define STONE_PROBABILITY 0
#define DEFAULT_ITERATIONS - 1
#define DEFAULT_RULE 1 
#define DEFAULT_MOISTURE_ROOTS 0 

class Args{
public:
    int width = DEFAULT_WIDTH;
    int height = DEFAULT_HEIGHT;
    int timeout = DEFAULT_TIMEOUT;
    bool no_color_flg = false;
    bool visulize_stdout_flg = false;
    std::string cell_symb = "default";
    int stone_probability = STONE_PROBABILITY;
    int iterations = DEFAULT_ITERATIONS;
    int rule = DEFAULT_RULE;
    float moisture = DEFAULT_MOISTURE;
    int moisture_roots_to_plant = DEFAULT_MOISTURE_ROOTS;

    // constructors
    Args(int argc, char **argv);
};

#endif // __ARGS_H__