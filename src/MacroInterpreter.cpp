#include "MacroInterpreter.h"

const static char *TOKEN_REGEX = "(\\[|\\]|#[^\\n]*|=|;|-?[0-9]*\\.?[0-9]+|[A-Za-z0-9_-]+)";
const static char *COMMENT_REGEX = "#[^\\n]*";
const static char *COLON_REGEX = ":";
const static char *SEMICOLON_REGEX = ";";

const static std::regex TOKEN{TOKEN_REGEX};
const static std::regex COMMENT{COMMENT_REGEX};
const static std::regex COLON{COLON_REGEX};
const static std::regex SEMICOLON{SEMICOLON_REGEX};


// Constructor
MacroInterpreter::MacroInterpreter()
{
}

// Destructor
MacroInterpreter::~MacroInterpreter()
{
}

/**
 * Reads through data and puts every token in tokens
 *
 * @param data, pointer to c-string containing the data to tokenize
 * @param tokens, pointer to vector of c-strings to store tokens in
 */
void MacroInterpreter::tokenize(const char **data, std::vector <char*> *tokens)
{
}

/**
 * Reads through file and creates macros in InputHandler and OutputHandler
 *
 * @param fileName, c-string containing the name of the file to read from 
 */
void MacroInterpreter::parseFile(char *fileName)
{
}
