
#ifndef __ARGS_H__
#define __ARGS_H__
#include <string>
#include "./grid.h"

class Args{
    public:
        int width = DEFAULT_WIDTH;
        int height = DEFAULT_HEIGHT;
        int timeout = DEFAULT_TIMEOUT;
        bool no_color_flg = false;
        std::string cell_symb = "default";

        // constructors
        Args(int argc, char **argv);
};

#endif // __ARGS_H__
