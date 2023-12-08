
#ifndef __VISUALIZER_H__
#define __VISUALIZER_H__
#include <string>
#include <vector>
#include "./cell.h"
#include "./args.h"
#include "./const.h"

class Visualizer {
    public:
        bool no_color_flg = false;
        bool visulize_stdout_flg = false;
        int width = 0;
        int height = 0;
        std::string cell_symbol;

        // constructor
        Visualizer(Args args);
        void draw(std::vector<std::vector<int>> grid);
};

#endif // __VISUALIZER_H__