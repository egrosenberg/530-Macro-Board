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
    m_VK_Table = new std::unordered_map<std::string, short int>();

    importVKC(m_VK_Table);
}

// Destructor
MacroInterpreter::~MacroInterpreter()
{
    delete m_VK_Table;
}


/**
 *  converts c-string to short int based on it's correlating VK_CODE value
 *
 * @param code, c-string containing VK_CODE to convert
 * @return short int containing the value corresponding to the VK_CODE, -1 if error
 */
short int MacroInterpreter::getVKC(std::string code)
{
    auto it = m_VK_Table->find(code);
    if (it != m_VK_Table->end())
    {
        std::cout << it->second;
        return it->second;
    }
    return -1;
}

/**
 * Reads through VK_CODES csv file and stores each pair of code and int in a map
 *
 * @param table, pointer to unordered_map to store VK_CODES and their corresponding values
 */
void MacroInterpreter::importVKC(std::unordered_map <std::string, short int> *table)
{
    std::ifstream *vkcFile = new std::ifstream(VK_CODE_PATH);
    if (!vkcFile->is_open())
    {
        std::cerr << "ERROR: Unable to open VK_CODE file\n";
    }

    std::string token;
    while (std::getline(*vkcFile, token, ','))
    {
        std::string codeStr;
        std::getline(*vkcFile, codeStr, ',');
        vkcFile->ignore();
        short int code = strtol(codeStr.c_str(), NULL, 16);
        
        (*table)[token] = code;
    }
    delete vkcFile;
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
