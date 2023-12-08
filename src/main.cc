#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>
#include "./main.h"

void test(Args args) {
    Grid grid(args);
    grid.place_stones();
    Visualizer visualizer(args);

    std::ofstream data("./data/data.txt");
    data.close();

    visualizer.draw_grid(grid);
}

int main(int argc, char** argv) {
    Args args(argc, argv);
    test(args);

    return 0;
}