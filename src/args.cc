#include <iostream>
#include <unistd.h>
#include "./args.h"


Args::Args(int argc, char** argv) {
    int opt;
    while((opt = getopt(argc, argv, "hn")) != -1){
        switch(opt) {
            case 'h':
                std::cout << "usage: "<< std::endl;
                break;
            case 'n':
                this->no_color_flg = true;
                break;
            default:
                std::cout << "ERROR" << std::endl;
                exit(1);
        }
    }
}