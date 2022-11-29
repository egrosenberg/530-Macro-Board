#ifndef _OUTPUT_HANDLER_H_
#define _OUTPUT_HANDLER_H_

#include "MacroBoard.h"

class OutputHandler
{
private:
    static OutputHandler *m_SingletonInstance;
    std::vector<Macro_Board::MacroPkg*> *m_MacroList;

public:
    OutputHandler();
    virtual ~OutputHandler();

    static OutputHandler *getSingleton();

    int addMacro(unsigned int ID, std::vector <INPUT>* inputList, int mode, std::string* run);
    int triggerMacro(unsigned int ID, int mode = 0, HWND *win = NULL);
    int triggerMacro(std::vector<INPUT> *inputKeys);
};

#endif
