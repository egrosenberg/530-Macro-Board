#ifndef _MACRO_INTERPRETER_H_
#define _MACRO_INTERPRETER_H_

#include <string>
#include <regex>

#include "MacroBoard.h"

class MacroInterpreter
{
private:
    OutputHandler *m_OutputHandler;
    InputHandler *m_InputHandler;

    void tokenize(const char **data, std::vector <char*> *tokens);
    void parseFile(char *fileName);
public:
    MacroInterpreter();
    virtual ~MacroInterpreter();
};

#endif
