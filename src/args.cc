#include <iostream>
#include <unistd.h>
#include "./args.h"


Args::Args(int argc, char** argv) {
    int opt;
    while((opt = getopt(argc, argv, "hn")) != 1){
        switch(opt) {
            case 'h':
                std::cout << "usage: "<< std::endl;
            case 'n':
                this->no_color_flg = true;
            default:
                std::cout << "default" << std::endl;
                exit(1);
        }
    }
}