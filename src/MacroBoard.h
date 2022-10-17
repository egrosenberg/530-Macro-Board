#ifndef _MACRO_BOARD_H_
#define _MACRO_BOARD_H_

#include <windows.h> // Windows API, hooks + input, etc.

namespace Macro_Board
{
    struct
    {
        unsigned int ID;
        INPUT *inputList;
    } MacroPkg;
}

#endif
