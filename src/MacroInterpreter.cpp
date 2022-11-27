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
MacroInterpreter::MacroInterpreter(char *path)
{
    m_VK_Table = new std::unordered_map<std::string, WORD>();
    m_LastID = 0;
    m_InputHandler = InputHandler::getSingleton();
    m_OutputHandler = OutputHandler::getSingleton();

    importVKC(m_VK_Table);

    parseFile(path);
}

// Destructor
MacroInterpreter::~MacroInterpreter()
{
    delete m_VK_Table;
}


/**
 *  converts c-string to WORD based on it's correlating VK_CODE value
 *
 * @param code, c-string containing VK_CODE to convert
 * @return WORD containing the value corresponding to the VK_CODE, return >256 if error
 */
WORD MacroInterpreter::getVKC(std::string code)
{
    auto it = m_VK_Table->find(code);
    if (it != m_VK_Table->end())
    {
        return it->second;
    }
    return 400;
}

/**
 * Reads through VK_CODES csv file and stores each pair of code and int in a map
 *
 * @param table, pointer to unordered_map to store VK_CODES and their corresponding values
 */
void MacroInterpreter::importVKC(std::unordered_map <std::string, WORD> *table)
{
    std::ifstream *vkcFile = new std::ifstream(VK_CODE_PATH);
    if (!vkcFile->is_open())
    {
        std::cerr << "ERROR: Unable to open VK_CODE file\n";
        return;
    }

    std::string token;
    while (std::getline(*vkcFile, token, ','))
    {
        std::string codeStr;
        std::getline(*vkcFile, codeStr, ',');
        vkcFile->ignore();
        WORD code = strtol(codeStr.c_str(), NULL, 16);
        
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
void MacroInterpreter::tokenize(const std::string *data, std::vector <std::string*> *tokens)
{
    // Iterator for regex tokens
    std::sregex_token_iterator tokenIT{data->begin(), data->end(), TOKEN};
    std::sregex_token_iterator iterEnd;

    // Iterate through all tokens
    while (tokenIT != iterEnd)
    {
        std::string *token = new std::string();
        *token = *tokenIT;

        // don't append it the token is a comment
        if (!std::regex_match(*token, COMMENT))
        {
            tokens->push_back(token);
        }
        tokenIT++;
    }
}

/**
 * Converts shor int into INPUT object
 *
 * @param vkCode, virtual key code to convert to INPUT
 * @param keyUp, bool stating whether it is a keyUp press
 * @param input, pointer to INPUT object to store in
 */
void MacroInterpreter::makeINPUT(WORD vkCode, bool keyUp, INPUT *input)
{
    input->type = INPUT_KEYBOARD;
    input->ki.wVk = vkCode;
    input->ki.wScan = (WORD)MapVirtualKey(vkCode, 0);
    input->ki.dwFlags = KEYEVENTF_SCANCODE;
    // Add unicode tag if unicode
    if (vkCode >= 0x30 && vkCode <= 0x5A)
    {
        input->ki.dwFlags |= KEYEVENTF_UNICODE;
    }
    if (keyUp)
    {
        input->ki.dwFlags |= KEYEVENTF_KEYUP;
    }
}

/**
 * Splits input string into two separate strings , one containing the macro input,
 * the second containing macro output
 *
 * @param in, pointer to string containing macro to be split
 * @param first, pointer to string to hold first half of macro
 * @param second, pointer to string to hold second half of macro
 * @return bool, true if successful, false if not
 */
bool MacroInterpreter::splitMacro(std::string *in, std::string *first, std::string *second)
{
    // Find position of colon in macro
    std::size_t pos = in->find(':');

    if (pos == std::string::npos)
    {
        return false; // ERROR: not found
    }

    // Set first to string up to colon
    *first = in->substr(0, pos);
    // Set second to string after colon
    *second = in->substr(pos + 1);

    return true;
}

/**
 * Reads through line and creates a macro in inputHandler and outputHandler based on input
 *
 * @param line, string containing line to be converted to macro
 */
void MacroInterpreter::makeMacro(std::string *line)
{
    // strings to hold our input and output for the macro
    std::string *input = new std::string(), *output = new std::string();
    // Split line
    bool split = splitMacro(line, input, output);
    if (!split)
    {
        std::cerr << "ERROR: could not split macro: " << *line << '\n';
        return;
    }

    // vector to hold tokens we are currently working with
    std::vector <std::string*> *tokens = new std::vector<std::string*>();

    // Tokenize and create macro input
    tokenize(input, tokens);
    // vector to hold key bind, will be stored in InputHandler
    std::vector <WORD> *inCodes = new std::vector<WORD>();
    // Iterate through all input tokens and add their vk-codes
    for (auto & token : *tokens)
    {
        WORD code = getVKC(*token);
        if (code > 256)
        {
            std::cerr << "ERROR: Invalid VK_CODE: " << *token << '\n'; // ERROR
        }

        inCodes->push_back(code);
    }
    m_InputHandler->addMacro(m_LastID, inCodes);

    // Clear tokens buffer
    tokens->clear();
    // Tokenize macro output
    tokenize(output, tokens);
    // vector to hold INPUTs for macro out
    std::vector <INPUT> *outputs = new std::vector<INPUT>();
    // Iterate through all output tokens and add them as INPUTs
    for (auto & token : *tokens)
    {
        bool is_up = true;
        bool is_down = true;
        if (token->length() > 3 && (token->substr(token->size()-3, 3) == "_UP"))
        {
            is_down = false;
            *token = token->substr(0, token->size()-3);
        }
        else if (token->length() > 5 && (token->substr(token->size()-5, 5), "_DOWN"))
        {
            is_up = false;
            *token = token->substr(0, token->size()-5);
        }
        
        WORD code = getVKC(*token);
        if (code > 256)
        {
            std::cerr << "ERROR: Invalid VK_CODE: " << *token << '\n'; // ERROR
        }

        INPUT down, up;

        if (is_down)
        {
            makeINPUT(code, false, &down);
            outputs->push_back(down);
        }
        if(is_up)
        {
            makeINPUT(code, true, &up);
            outputs->push_back(up);
        }
    }
    m_OutputHandler->addMacro(m_LastID, outputs);

    ++m_LastID;

    delete input;
    delete output;
    delete tokens;    
}

/**
 * Reads through file and creates macros in InputHandler and OutputHandler
 *
 * @param fileName, c-string containing the name of the file to read from 
 */
void MacroInterpreter::parseFile(char *fileName)
{
    // Create a new input stream from file containing macros
    std::ifstream *inFile = new std::ifstream(fileName);
    // Verify the file opened properly
    if (!inFile->is_open())
    {
        std::cerr << "ERROR: UNABLE TO OPEN MACROS FILE\n";
        return;
    }
    
    std::string currentLine;
    while (std::getline(*inFile, currentLine))
    {
        makeMacro(&currentLine);
    }
}

