// Implementation of celluar automata
// authors: Tomas Fratrik (xfratr01), Patrik Jezko (xjesko01)
#include <iostream>
#include <iomanip>
#include <fstream>  // For file handling
#include <cstdlib>
#include <ctime>

#define MOISTURE 1.0

struct Cell {
    float moisture;
    int rootx;
    int rooty;
    bool is_water_root;
};

class Grid {
public:
    Grid(int width, int height) : width(width), height(height) {
        // Initialize the grid with cells having random moisture values
        grid = new Cell*[height];
        for (int i = 0; i < height; ++i) {
            grid[i] = new Cell[width];
            for (int j = 0; j < width; ++j) {
                grid[i][j].moisture = MOISTURE;
                grid[i][j].rootx = j;
                grid[i][j].rooty = i;
                grid[i][j].is_water_root = false;
            }
        }
    }

    ~Grid() {
        // Deallocate memory
        for (int i = 0; i < height; ++i) {
            delete[] grid[i];
        }
        delete[] grid;
    }

    void printMoisturesToFile(const std::string& filename) {
        std::ofstream outputFile(filename);
        if (!outputFile.is_open()) {
            std::cerr << "Error: Unable to open file " << filename << std::endl;
            return;
        }

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                outputFile << std::fixed << std::setprecision(2) << grid[i][j].moisture;

                if (j < width - 1) {
                    outputFile << " | ";
                }
            }

            outputFile << std::endl;

            if (i < height - 1) {
                for (int j = 0; j < width - 1; ++j) {
                    outputFile << "----" ;
                }
                outputFile << std::endl;
            }
        }

        outputFile.close();
    }

    bool isWaterRootsChild(int rootx, int rooty, int x, int y){
        return (rootx == x && rooty == y);
    }

    void setMoistureRadius(int y, int x, float base_moisture) {
        float excess_moisture = base_moisture - 1.0;

        grid[y][x].moisture = base_moisture;
        grid[y][x].is_water_root = true;
        int steps = static_cast<int>(excess_moisture * 10);
        float set_moisture = excess_moisture - 0.1;

        for (int i = 1; i <= steps; i++) {
            for (int j = -i; j <= i; j++) {
                int new_y = y - i;
                int new_x = x + j;

                if (new_y >= 0 && new_y < height && new_x >= 0 && new_x < width && !grid[new_y][new_x].is_water_root && !isWaterRootsChild(grid[new_y][new_x].rootx, grid[new_y][new_x].rooty, x, y)) {
                    grid[new_y][new_x].moisture = std::min(2.0f, grid[new_y][new_x].moisture + set_moisture);
                    grid[new_y][new_x].rootx = x;
                    grid[new_y][new_x].rooty = y;
                }

                new_y = y + i;
                new_x = x + j;

                if (new_y >= 0 && new_y < height && new_x >= 0 && new_x < width && !grid[new_y][new_x].is_water_root && !isWaterRootsChild(grid[new_y][new_x].rootx, grid[new_y][new_x].rooty, x, y)) {
                    grid[new_y][new_x].moisture = std::min(2.0f, grid[new_y][new_x].moisture + set_moisture);
                    grid[new_y][new_x].rootx = x;
                    grid[new_y][new_x].rooty = y;
                }

                new_y = y + j;
                new_x = x - i;

                if (new_y >= 0 && new_y < height && new_x >= 0 && new_x < width && !grid[new_y][new_x].is_water_root && !isWaterRootsChild(grid[new_y][new_x].rootx, grid[new_y][new_x].rooty, x, y)) {
                    grid[new_y][new_x].moisture = std::min(2.0f, grid[new_y][new_x].moisture + set_moisture);
                    grid[new_y][new_x].rootx = x;
                    grid[new_y][new_x].rooty = y;
                }

                new_y = y + j;
                new_x = x + i;

                if (new_y >= 0 && new_y < height && new_x >= 0 && new_x < width && !grid[new_y][new_x].is_water_root && !isWaterRootsChild(grid[new_y][new_x].rootx, grid[new_y][new_x].rooty, x, y)) {
                    grid[new_y][new_x].moisture = std::min(2.0f, grid[new_y][new_x].moisture + set_moisture);
                    grid[new_y][new_x].rootx = x;
                    grid[new_y][new_x].rooty = y;
                }
            }
            set_moisture -= 0.1;
        }
    }

    void setWaterRoots(int number_of_roots, float base_moisture){
        for (int i = 0; i < number_of_roots; i++){
            int randomX = rand() % width;
            int randomY = rand() % height;
            setMoistureRadius(randomY, randomX, base_moisture);
        }
    }

private:
    int width;
    int height;
    Cell** grid;
};

int main() {
    std::srand(time(0));
    const int gridSize = 50;

    Grid myGrid(gridSize, gridSize);
    myGrid.setWaterRoots(3, 2.0);
    myGrid.printMoisturesToFile("test.txt");

    return 0;
}