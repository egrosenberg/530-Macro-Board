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
        MacroPkg(unsigned int id, INPUT *inputs, unsigned int inputSize) : 
            ID{id},
            inputList{inputs},
            sizeOfInputs{inputSize}
            {}
    } MacroPkg;
}

class MacroHolder;
class InputHandler;
class OutputHandler;
class MacroInterpreter;

#include "MacroHolder.h"
#include "OutputHandler.h"
#include "InputHandler.h"
#include "MacroInterpreter.h"

#define VK_LIST_SIZE 255

#endif
