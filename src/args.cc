#include <iostream>
#include <unistd.h>
#include "./args.h"

Args::Args(int argc, char** argv) {
    int opt;
    while((opt = getopt(argc, argv, "vnw:h:c:t:s:")) != -1){
        switch(opt) {
            case 'h':
                this->height = atoi(optarg);
                break;
            case 'w':
                this->width = atoi(optarg);
                break;
            case 'n':
                this->no_color_flg = true;
                break;
            case 'c':
                this->cell_symb = optarg;
                break;
            case 't':
                this->timeout = atoi(optarg);
                break;
            case 'v': 
                this->visulize_stdout_flg = true;
                break;
            case 's':
                this->stone_probability = atoi(optarg);
                break;
            default:
                std::cout << "ARG ERROR" << std::endl;
                exit(1);
        }
    }
}