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
}

// Delete member variables in mem
OutputHandler::~OutputHandler()
{
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
    return -1;
}

/**
 * Send each input in list
 *
 * @param **INPUT, pointer to array of inputs to send
 * @return positive number if successful, 0 or negative if not
 */
int OutputHandler::triggerMacro(INPUT **inputs)
{
}
