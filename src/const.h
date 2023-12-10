// Implementation of celluar automata
// authors: Tomas Fratrik (xfratr01), Patrik Jezko (xjesko01)
#ifndef _CONST_H_
#define _CONST_H_
#include <string>

namespace Const {
    const std::string DATA_FILE_PATH = "./data/data.txt";

    const std::string BLACK = "\033[30m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string MAGENTA = "\033[35m";
    const std::string WHITE = "\033[37m";
    const std::string RESET = "\033[0m";
    const std::string GRAY = "\033[38;2;128;128;128m";


    // Soil moisture
    const std::string BROWN_SOIL = "\033[38;2;191;128;64m";
    const std::string BROWN_1 = "\033[38;2;172;115;57m";
    const std::string BROWN_2 = "\033[38;2;153;102;51m";
    const std::string BROWN_3 = "\033[38;2;134;89;45m";
    const std::string BROWN_4 = "\033[38;2;96;64;32m";

    const std::string CLEAR_SCREEN =  "\033[H\033[2J";

    const std::string BIG_SQUARE = "██";
    const std::string SMALL_SQUARE = "■";
    const std::string DOT = "•";
    const std::string DEFAULT_CELL_SYMB = Const::BIG_SQUARE;
};

#endif // _CONST_H_