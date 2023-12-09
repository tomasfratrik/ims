#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>
#include "./main.h"
#include "./simulation.h"
#include "./macros.h"

int main(int argc, char** argv) {
    Args args(argc, argv);
    Grid grid(args);
    Visualizer visualizer(args);
    Simulation sim(&args, &grid, &visualizer);
    sim.run();

    // TODO: do we need clean memory ?, if so
    // there mby should be a destructors, but im too dumb
    // for that, idk
    // for each grid cycle, we don't create more memory (cells)
    // we just change the state of the cells, so mby we don't need 
    // to clean memory, but idk

    return 0;
}