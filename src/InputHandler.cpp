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

    // Convert lParam to low level keyboard event
    PKBDLLHOOKSTRUCT hStruct = (PKBDLLHOOKSTRUCT)(lParam);
    // Grab virtual keycode from struct
    DWORD vCode = hStruct->vkCode;
    int vcInt = (int)(vCode);

    // Only check macros on KeyPress events
    if (wParam == WM_KEYDOWN && vcInt != m_LastKey)
    {
        // Iterate through all MacroHolders
        for (auto & macroHolder : *m_MacroHolders)
        {
            macroHolder->checkTrigger(vcInt);
        }
        m_LastKey = vcInt;
    }
    // Reset lastkey if key is released
    if (wParam == WM_KEYUP && vcInt == m_LastKey)
    {
        m_LastKey = -1;
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
    m_LastKey = -1;

    m_MacroHolders = new std::vector<MacroHolder*>();

    m_KeyPressHook = SetWindowsHookEx
    (
        WH_KEYBOARD_LL,
        staticKeyHook,
        hInstance,
        0
    );
}

// Delete member variables from memory
InputHandler::~InputHandler()
{
    delete m_MacroHolders;
    UnhookWindowsHookEx(m_KeyPressHook);
}

/**
 * Create MacroHolder and add to vector
 *
 * @param ID, id of macro
 * @param *keyBind, pointer to vector of corresponding VK_KEYCODE values
 * @return int, positive if successful, 0 or negative if error
 */
int InputHandler::addMacro(int ID, std::vector <int> *keyBind)
{
    // Prevent duplicate Macro IDs
    for (auto & macroHolder : *m_MacroHolders)
    {
        if (macroHolder->getID() == ID)
        {
            std::cerr << "ERROR: Duplicate macro not added!" << std::endl;
            return -1; // Womp womp
        }
    }

    // Create new MacroHolder and add to vector
    MacroHolder *toAdd = new MacroHolder(ID, keyBind);
    m_MacroHolders->push_back(toAdd);

    return 1; // Success!
}

/**
 * Delete MacroHolder from vector
 *
 * @param ID, id of macro to remove
 */
void InputHandler::releaseHook(int ID)
{
    // Iterate through MacroHolders and remove whichever MacroHolder has a matching ID
    m_MacroHolders->erase(
        std::remove_if(
            m_MacroHolders->begin(), m_MacroHolders->end(),
            [ID](const auto & holder) 
            {
                return holder->getID() == ID;
            }
            ), m_MacroHolders->end());

}

