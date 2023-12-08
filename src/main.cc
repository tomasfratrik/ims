#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>
#include "./main.h"

void test(Args args) {
    Grid grid(args);
    Visualizer visualizer(args);
    // std::vector<std::vector<CellType>> matrix(args.height, std::vector<CellType>(args.width));

    std::ofstream data("./data/data.txt");
    data.close();

    visualizer.draw_grid(grid);

    // int T = 10;
    // while(T--) {
    //     if (visualizer.visulize_stdout_flg) {
    //         std::cout << Const::CLEAR_SCREEN;
    //         std::cout << std::endl;
    //     }

    //     for (int y = 0; y < args.height; y++) {
    //         for (int x = 0; x < args.width; x++) {
    //             // grid.grid[i][j] = rand() % CellType::NO_TYPES;
    //             Cell cell(x,y);
    //             grid.grid[x][y] = cell;
    //         }
    //     }
    //     visualizer.draw(grid); 
    //     if (visualizer.visulize_stdout_flg) {
    //         std::this_thread::sleep_for(std::chrono::milliseconds(args.timeout));
    //         std::cout << std::endl;
    //     }
    // }
}

int main(int argc, char** argv) {
    Args args(argc, argv);
    test(args);

    return 0;
}