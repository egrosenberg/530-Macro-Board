#ifndef _MACRO_BOARD_H_
#define _MACRO_BOARD_H_

#include <windows.h> // Windows API, hooks + input, etc.
#include <vector>

namespace Macro_Board
{
    typedef struct MacroPkg
    {
        unsigned int ID;
        INPUT *inputList;
        unsigned int sizeOfInputs;
    } MacroPkg;
}

class MacroHolder;
class InputHandler;
class OutputHandler;

#include "MacroHolder.h"
#include "OutputHandler.h"
#include "InputHandler.h"

#define VK_LIST_SIZE 255

#endif
