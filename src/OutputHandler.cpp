#include "OutputHandler.h"

OutputHandler *OutputHandler::m_SingletonInstance = NULL;


/**
 * Retrieves / creates the *only* instance of this class we use.
 *
 * @return Singleton instance of class.
 */
OutputHandler *OutputHandler::getSingleton()
{
    if (m_SingletonInstance == NULL)
    {
        m_SingletonInstance = new OutputHandler();
    }
    return m_SingletonInstance;
}

// Initialize member variables
OutputHandler::OutputHandler()
{
    m_MacroList = new std::vector<Macro_Board::MacroPkg*>();
}

// Delete member variables in mem
OutputHandler::~OutputHandler()
{
    delete m_MacroList;
}

/**
* Create INPUT array from inputList of vectors
* Create MacroPkg from INPUT array and ID
* Append MacroPkg to m_MacroList
* 
* @param ID, ID of macro to be added to MacroPkg
* @param inputList, list of inputs sent during tokenizer
* @return positive number if success, negative if failure
*/
int OutputHandler::addMacro(unsigned int ID, std::vector <INPUT>* inputList)
{
    // Check for duplicate macros
    for(auto & macro : *m_MacroList)
    {
        if (macro->ID == ID)
        {
            return -1;
        }
    }

    INPUT *inputKeys = new INPUT[inputList->size()];    //convert inputList from vector to array of INPUT
    std::copy(inputList->begin(), inputList->end(), inputKeys);
    
    //create MacroPkg, pass the given ID and converted inputList
    Macro_Board::MacroPkg *macro = new Macro_Board::MacroPkg(ID, inputKeys, inputList->size());
    m_MacroList->push_back(macro);  //append new MacroPkg to m_MacroList vector

    std::cout << "Added Macro #" << ID << '\n';

    return 1;
}



/**
 * Send inputs of Corresponding Macro
 *
 * @param ID, id if macro to call
 * @param mode, 0 = normal, 1 = send to window (TBD)
 * @return positive number if successful, 0 or negative if not
 */
int OutputHandler::triggerMacro(unsigned int ID, int mode, HWND *win)
{
    
    //iterate every macro in m_MacroList, if it matches the ID passed to the function, then trigger the macro to produce keystrokes/clicks/mouse motion
    for (auto & macro : *m_MacroList)                
    {
        if (macro->ID == ID)
        {
            std::cout << ID << ": ";
            UINT uSent = SendInput(macro->sizeOfInputs, macro->inputList, sizeof(INPUT));      
            if (uSent == macro->sizeOfInputs)
            {
                std::cout << "success\n";
                return 1;
            }
            else
            {
                std::cout << "failure\n";
                return -1;
            }
        }
    }

    return -1;
}

/**
 * Send each input in list
 *
 * @param **INPUT, pointer to array of inputs to send
 * @return positive number if successful, 0 or negative if not
 */
int OutputHandler::triggerMacro(std::vector<INPUT> *inputKeys)
{
    return -1;
}
