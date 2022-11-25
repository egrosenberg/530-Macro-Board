#ifndef _MACRO_INTERPRETER_H_
#define _MACRO_INTERPRETER_H_

#define VK_CODE_PATH "resources/VK_CODES.csv"

#include <string>
#include <regex>
#include <fstream>
#include <unordered_map>
#include <iostream>

#include "MacroBoard.h"

class MacroInterpreter
{
private:
    OutputHandler *m_OutputHandler;
    InputHandler *m_InputHandler;

    std::unordered_map <std::string, short int> *m_VK_Table;

    void importVKC(std::unordered_map <std::string, short int>*table);
    short int getVKC(std::string code);

    void tokenize(const char **data, std::vector <char*> *tokens);
    void parseFile(char *fileName);
public:
    MacroInterpreter();
    virtual ~MacroInterpreter();
};

#endif
