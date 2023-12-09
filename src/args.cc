#include <iostream>
#include <unistd.h>
#include <string>
#include "./args.h"

Args::Args(int argc, char** argv) {
    int opt;
    while((opt = getopt(argc, argv, "vnw:h:c:t:s:i:r:m:")) != -1){
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
            case 'i':
                this->iterations = atoi(optarg);
                break;
            case 'r':
                this->rule = atoi(optarg);
                break;
            case 'm':
                this->moisture = std::stof(optarg);
                break;
            default:
                std::cout << "ARG ERROR" << std::endl;
                exit(1);
        }
    }
    // todo: check for valid args
    // is it number? , rule 1-4, etc
    // for how many rules tehre are us NO_RULES - 1 

    // a aj max iteracie su height -1 
    // lebo inac by si uz zapisoval pod pole

    // min widht a height aspon 10 ? at tu nemusime riesit nejake
    // cringe edge cases
}