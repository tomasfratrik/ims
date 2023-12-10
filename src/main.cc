// Implementation of celluar automata
// authors: Tomas Fratrik (xfratr01), Patrik Jezko (xjesko01)
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>
#include "./main.h"
#include "./simulation.h"
#include "./macros.h"

int main(int argc, char** argv) {
    std::srand(time(0));
    Args args(argc, argv);
    Grid grid(args);
    Visualizer visualizer(&grid);
    Simulation sim(&args, &grid, &visualizer);
    sim.run();

    return 0;
}