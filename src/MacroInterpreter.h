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

    std::unordered_map <std::string, WORD> *m_VK_Table;
    WORD m_LastID;

    void importVKC(std::unordered_map <std::string, WORD>*table);
    WORD getVKC(std::string code);

    void tokenize(const std::string *data, std::vector <std::string*> *tokens);
    void makeINPUT(std::string code, bool keyUp, INPUT *input);
    bool splitMacro(std::string *in, std::string *first, std::string *second, std::string* third);
    void makeMacro(std::string *line);
    void parseFile(const char *fileName);
public:
    MacroInterpreter(const char *path);
    virtual ~MacroInterpreter();
};

#endif
