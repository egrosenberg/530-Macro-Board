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
int OutputHandler::addMacro(unsigned int ID, std::vector <INPUT>* inputList, int mode, std::string* run)
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
    Macro_Board::MacroPkg *macro = new Macro_Board::MacroPkg(ID, inputKeys, inputList->size(), mode, run);
    m_MacroList->push_back(macro);  //append new MacroPkg to m_MacroList vector

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
    
    /** 
    * iterate every macro in m_MacroList, if it matches the ID passed to the function, then trigger the macro to produce keystrokes / clicks / mouse motion
    * if mode is 0 there's no app to open before outputting
    * if mode is 1, open the app under macro->run_
    */
   
    for (auto& macro : *m_MacroList)
    {
        if (macro->ID == ID)    //find the matching ID
        {
            if (macro->mode == 0)
            {
                UINT uSent = SendInput(macro->sizeOfInputs, macro->inputList, sizeof(INPUT));
                if (uSent == macro->sizeOfInputs)
                {
                    return 1;
                }
                    
            }
               
            if (macro->mode == 1)
            {
                //convert macro->run_ to char array
                std::string temp = macro->run_->c_str();
                char* run = &temp[0]; 


                STARTUPINFO si = { 0 };
                PROCESS_INFORMATION pi = { 0 };
                BOOL bSuccess = CreateProcessA(TEXT(run), NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);
                if (bSuccess)
                {
                    Sleep(2000);
                        
                    UINT uSent = SendInput(macro->sizeOfInputs, macro->inputList, sizeof(INPUT));
                    if (uSent == macro->sizeOfInputs)
                    { 
                        //WaitForSingleObject(pi.hProcess, INFINITE);
                        //CloseHandle(pi.hProcess);
                        //CloseHandle(pi.hThread);
                        return 1; 
                    }
                }
                    
                    
                //wait until child process exits.
                    
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
