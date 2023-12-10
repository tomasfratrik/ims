// Implementation of celluar automata
// authors: Tomas Fratrik (xfratr01), Patrik Jezko (xjesko01)

#include <iostream>
#include <unistd.h>
#include <string>
#include "./args.h"

Args::Args(int argc, char** argv) {
    int opt;
    try {
        while((opt = getopt(argc, argv, "vnw:h:c:t:s:i:r:m:p:")) != -1){
            switch(opt) {
                case 'h':
                    this->height = std::stoi(optarg);
                    if (this->height < 10){
                        std::cout << "Height too small, using 10 instead" << std::endl;
                        this->height = 10;
                    }
                    break;
                case 'w':
                    this->width = std::stoi(optarg);
                    if (this->width < 10){
                        std::cout << "Width too small, using 10 instead" << std::endl;
                        this->width = 10;
                    }
                    break;
                case 'n':
                    this->no_color_flg = true;
                    break;
                case 'c':
                    //todo: isnt this only in visualizer? do we still need it? (cell_symb)
                    this->cell_symb = optarg;
                    break;
                case 't':
                    // todo: dont know how to check really, only in visualizer? (timeout)
                    this->timeout = std::stoi(optarg);
                    break;
                case 'v': 
                    this->visulize_stdout_flg = true;
                    break;
                case 's':
                    this->stone_probability = std::stoi(optarg);
                    break;
                case 'i':
                    this->iterations = std::stoi(optarg);
                    break;
                case 'r':
                    this->rule = std::stoi(optarg);
                    if (this->rule < 1 || this->rule > 4){
                        std::cout << "Unknown rule!" << std::endl;
                        std::cout << "Using default rule: Rule " << DEFAULT_RULE << std::endl;
                        this->rule = DEFAULT_RULE;
                    }
                    break;
                case 'm':
                    this->moisture = std::stof(optarg);
                    if (this->moisture < 1 || this->moisture > 2){
                        std::cout << "Moisture needs to be between 1 and 2!" << std::endl;
                        std::cout << "Using default moisture: " << DEFAULT_MOISTURE << std::endl;
                    }
                    break;
                case 'p':
                    this->moisture_roots_to_plant = std::stoi(optarg);
                    break;
                default:
                    std::cout << "ARG ERROR" << std::endl;
                    exit(1);
            }
        }
    } catch (const std::exception& e) {
        std::cout << "Error while parsing arguments: " << e.what() << std::endl;
        exit(1);
    }

    //check iteration after all arguments are read (maybe there was not height specified yet)
    if (this->iterations == -1) {
        // std::cout << "Iterations not specified, using height" << std::endl;
        this->iterations = this->height;
        // test
    }

    // todo check for correctness of the changes
    // every stoi error will be cought in the catch block nad handled

    // todo: check for valid args ?????
    // ???????
    // for how many rules tehre are us NO_RULES - 1 
    // ???????
    // I dont understand
}