#ifndef _OUTPUT_HANDLER_H_
#define _OUTPUT_HANDLER_H_

#include "MacroBoard.h"

class OutputHandler
{
private:
    static OutputHandler *m_SingletonInstance;
    Macro_Board::MacroPkg *m_MacroList;
public:
    OutputHandler();
    virtual ~OutputHandler();

    static OutputHandler *getSingleton();

    int triggerMacro(unsigned int ID, int mode = 0, HWND *win = NULL);
    int triggerMacro(INPUT **inputs);
};

#endif
