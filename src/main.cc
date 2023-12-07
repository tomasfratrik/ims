#include <iostream>
#include "./args.h"

int main(int argc, char** argv) {
    Args args(argc, argv);
    if (args.no_color_flg) {
        std::cout << "no color" << std::endl;
    }
    // TODO: implement
    return 0;
}