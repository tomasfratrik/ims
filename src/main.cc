#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>
#include "./main.h"

void test(Args args) {
    // reset file
    std::ofstream data("./data/data.txt");
    data.close();

    Grid grid(args);
    grid.place_stones();
    // grid.place_root();
    Visualizer visualizer(args);


    visualizer.draw_grid(grid);
}

int main(int argc, char** argv) {
    std::srand(time(0));
    Args args(argc, argv);
    test(args);

    return 0;
}