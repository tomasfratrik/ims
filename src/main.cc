#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include "./args.h"
#include "./visualizer.h"
#include "./const.h"

void test(Args args) {
    Visualizer visualizer(args);
    std::vector<std::vector<int>> matrix(args.height, std::vector<int>(args.width));

    int T = 10;
    while(T--) {
        std::cout << Const::CLEAR_SCREEN;
        std::cout << std::endl;
        for (int i = 0; i < args.height; i++) {
            for (int j = 0; j < args.width; j++) {
                matrix[i][j] = rand() % CellState::NO_STATES;
            }
        }
        visualizer.draw(matrix); 
        std::this_thread::sleep_for(std::chrono::milliseconds(args.timeout));
        std::cout << std::endl;
    }
}

int main(int argc, char** argv) {
    Args args(argc, argv);
    test(args);

    return 0;
}