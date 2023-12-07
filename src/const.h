#ifndef _CONST_H_
#define _CONST_H_
#include <string>

namespace Const {
    const std::string BLACK = "\033[30m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN = "\033[36m";
    const std::string WHITE = "\033[37m";
    const std::string RESET = "\033[0m";

    const std::string CLEAR_SCREEN =  "\033[H\033[2J";

    const std::string BIG_SQUARE = "██";
    const std::string SMALL_SQUARE = "■";
    const std::string DOT = "•";
    const std::string DEFAULT_CELL_SYMB = Const::BIG_SQUARE;
};

#endif // _CONST_H_