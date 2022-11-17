#include "InputHandler.h"

static InputHandler *m_SingletonInstance = NULL;
 
/**
 * Retrieves / creates the *only* instance of this class we use.
 *
 * @param hInstance, OPTIONAL, HINSTANCE of program
 * @return Singleton instance of class.
 */
InputHandler *InputHandler::getSingleton(HINSTANCE hInstance)
{
    if (m_SingletonInstance == NULL)
    {
        if (hInstance == NULL)
        {
            std::cout << "ERROR, no HINSTANCE\n";
            return NULL;
        }
        m_SingletonInstance = new InputHandler(hInstance);
    }
    return m_SingletonInstance;
}

/**
 * Calls non-static keyHook function
 *
 * @param nCode, hook code
 * @param wParam, virtual-key code
 * @param lParam, a lot of stuff, convert to PKBDLLHOOKSTRUCT
 * @return ouput of local keyhook function
 */
LRESULT InputHandler::staticKeyHook(int nCode, WPARAM wParam, LPARAM lParam)
{
}


/**
 * Check what input is, update keys held
 * Run all macro checks
 *
 * @param nCode, hook code
 * @param wParam, virtual-key code
 * @param lParam, a lot of stuff, convert to PKBDLLHOOKSTRUCT
 * @return next hook to call
 */
LRESULT InputHandler::keyHook(int nCode, WPARAM wParam, LPARAM lParam)
{
}

/** 
 * Initialize member variables.
 * Set windows hook
 *
 * @param hInstance, HINSTANCE struct from application
 */
InputHandler::InputHandler(HINSTANCE hInstance)
{
}

// Delete member variables from memory
InputHandler::~InputHandler()
{
}

/**
 * Create MacroHolder and add to vector
 *
 * @param ID, id of macro
 * @param **inputs, pointer to array of inputs
 * @return int, positive if successful, 0 or negative if error
 */
int InputHandler::addMacro(int ID, INPUT **inputs)
{
}

/**
 * Delete MacroHolder from vector
 *
 * @param ID, id of macro to remove
 */
void InputHandler::releaseHook(int ID)
{
}

