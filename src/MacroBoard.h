#ifndef _MACRO_BOARD_H_
#define _MACRO_BOARD_H_

#include <windows.h> // Windows API, hooks + input, etc.
#include <vector>
#include <string>

namespace Macro_Board
{
    typedef struct MacroPkg
    {
        unsigned int ID;
        INPUT *inputList;
        unsigned int sizeOfInputs;
        int mode;
        std::string *run_;
        MacroPkg(unsigned int id, INPUT *inputs, unsigned int inputSize, int mode_, std::string *run_) : 
            ID{id},
            inputList{inputs},
            sizeOfInputs{inputSize},
            mode{mode_},
            run_{run_}
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

#define VK_LIST_SIZE 256

#endif
