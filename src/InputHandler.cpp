#include "InputHandler.h"

InputHandler *InputHandler::m_SingletonInstance = NULL;
 
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
    InputHandler *singleton = getSingleton();
    return singleton->keyHook(nCode, wParam, lParam);
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
    if (nCode < 0) // Keypress not properly logged, skip our hook
    {
        return CallNextHookEx(NULL, nCode, wParam, lParam);
    }

    // Store lParam as a low levek keyboard event
    PKBDLLHOOKSTRUCT hStruct = (PKBDLLHOOKSTRUCT)(lParam);

    // Only check macros on KeyPress events
    if (wParam == WM_KEYDOWN)
    {
        // Iterate through all MacroHolders
        for (auto & macroHolder : *m_MacroHolders)
        {
            macroHolder.checkTrigger();
        }
    }

    return CallNextHookEx(NULL, nCode,  wParam, lParam);
}

/** 
 * Initialize member variables.
 * Set windows hook
 *
 * @param hInstance, HINSTANCE struct from application
 */
InputHandler::InputHandler(HINSTANCE hInstance)
{
    m_KeyHeld = new bool[1]; // Currently unused, may remove later.

    m_MacroHolders = new std::vector<MacroHolder>();
}

// Delete member variables from memory
InputHandler::~InputHandler()
{
    delete m_MacroHolders;
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

